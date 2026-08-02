# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Working conventions

- Always make changes directly in the user's main working tree. Do not create or work in
  separate git worktrees unless the user explicitly states otherwise for a given task.
- Never run `git commit` or `git push` (or otherwise create commits/push to the repo). The user
  reviews and applies all diffs manually.

## What this is

Ferd is a C++20 train-line simulation game rendered with OpenGL (GLEW + GLFW), using ImGui for
debug UI, GLM for math, Eigen, and spdlog for logging. It targets Windows and is built via
mingw-w64 cross-compilation from Linux (the CMake toolchain forces
`CMAKE_SYSTEM_NAME Windows` and links `opengl32`/`ws2_32`/`glew32s.lib` even when invoked on
Linux).

## Build

The project uses CMake + Ninja. Dependencies (`ext/spdlog`, `ext/glm`, `ext/imgui`, `ext/eigen`,
`ext/googletest`) are git submodules; GLFW and GLEW are not submodules and must be manually
unpacked into `ext/glfw` and `ext/glew` (see `Dockerfile` for the exact versions/URLs — GLFW
3.4 win32 release, GLEW 2.1.0 win32 release).

```sh
git submodule init && git submodule update
```

Configure and build (cross-compiling to Windows, matching the existing `build/` cache):

```sh
CXX=/usr/bin/x86_64-w64-mingw32-g++ CC=/usr/bin/x86_64-w64-mingw32-gcc \
  cmake -S . -B build -G Ninja -DBUILD_FERD=ON -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

Key CMake options (all OFF by default):
- `BUILD_FERD` — build the `ferd` executable (`src/`)
- `BUILD_TESTS` — build the GoogleTest suite (`tests/`)

The core game/framework code always builds into the `ferdprj` static library regardless of these
flags, so compilation errors in `lib/` surface even with both options off.

Shader files in `src/shader/*.vertexshader` / `*.fragmentshader` are loaded via **hardcoded
absolute Windows paths** in `src/main.cpp` (e.g. `C:/git/ferd/src/shader/...`), a reflection of
the Windows target.

## Tests

Tests use GoogleTest (vendored in `ext/googletest`) and live under `tests/lib/...`, mirroring the
`lib/` source layout. Only `tests/lib/game/line` currently exists. Each test target is declared
via the `package_add_test(<name> <sources>)` macro in `tests/CMakeLists.txt` and compiles the
relevant `lib/` `.cpp` files directly (not linked against `ferd_lib`), plus mocks from
`tests/mocks/`.

Run with:

```sh
cmake -S . -B build -G Ninja -DBUILD_TESTS=ON
cmake --build build
ctest --test-dir build
```

To run a single test binary directly: `build/tests/lib/game/line/line_test`.

OpenGL calls are seamed behind the virtual `OpenGLWrapper` class
(`include/framework/OpenGLWrapper.hpp`) so geometry classes (`RectangleObject`, `LineObject`,
`CircleObject`) can be tested without a real GL context, using `tests/mocks/MockOpenGLWrapper.h`.

## Linting

CI (`.github/workflows/cpplint.yml`) runs `cpplint` on every PR:

```sh
cpplint --linelength 100 --filter=-legal/copyright,-build/c++11,-runtime/threadsafe_fn \
  --exclude ext --recursive .
```

`.clang-format` (Google-based) is also present for formatting, though note it sets
`ColumnLimit: 80`, narrower than cpplint's 100. Header guards follow the
`INCLUDE_<PATH>_<FILE>_HPP_` convention (e.g. `INCLUDE_GAME_RAIL_RAILPIECE_HPP_`).

## Architecture

### Library structure

`lib/` builds into `ferd_lib` (an INTERFACE target aggregating two real libraries):
- `ferd_framework` — windowing, OpenGL program/shader management, drawable geometry primitives
- `ferd_game` — game/simulation logic, depends on `ferd_framework`

Headers mirror this under `include/framework/` and `include/game/`.

### Rendering pipeline

`GraphicsFramework` (`framework/graphicsFramework.*`) is the top-level render/update orchestrator
driven from `main.cpp`'s loop (`Activate` → per-frame `Update`/`Render`/`swapBuffers`). It owns:
- A `WindowHandler` (GLFW window + ImGui debug overlay + camera input)
- Three `GraphicsProgram`s (shader pairs) for trains, lines, and stations
- A pointer to the active `World` and `Camera`

`World` (`game/world.*`) is the scene container: trains, line objects, rectangles, and stations to
be rendered each frame. It does not own simulation timing — `Train::Update` is driven externally.

Drawable primitives (`RectangleObject`, `LineObject`, `CircleObject` under
`framework/geometry/`) each wrap their own VAO/VBO state and issue calls through the injectable
`OpenGLWrapper`.

### Two parallel train-movement systems

This is important context for anything touching train movement — there are currently **two
independent systems** for how trains follow a route, at different stages of maturity:

1. **Line/Waypoint system** (`game/line.*`, `game/waypoint/`, `game/trainNavigator.*`,
   `game/trainPhysics.*`, `game/train.*`) — the system actually wired up and used in
   `src/main.cpp` today. A `Train` owns a `TrainNavigator` (tracks progress along a `Line`'s
   `Waypoint`/`Station` list) and a `TrainPhysics` (acceleration/velocity/state machine:
   `STOPPED_AT_STATION` / `ENROUTE` / `APPROACH`).

2. **Rail system** (`game/rail/`) — a newer, in-progress replacement (see recent commits "First
   draft of new rail system", "Added draft versions of StraightRailStation and StationSeeker").
   Built around a graph of `RailPiece`s (abstract; `StraightRailPiece` is the concrete
   implementation) connected via `RailConnection` nodes, each holding up to two rail pieces (A/B
   sides) and links to neighboring connections. `RailWalker` moves along the current `RailPiece`
   and hands off to the next one at a `RailConnection`; `StationSeeker` (extends `RailWalker`)
   adds arrival/departure state (`SeekerState`, `SeekerEvent`) for `StraightRailStation` pieces.
   This system is not yet wired into `main.cpp`.

When working on movement/navigation logic, check which system a file belongs to before assuming
behavior carries over between them.

### Physics/geometry primitives

`game/physics/kinematics.hpp` defines the shared `Vector2D`/`position_t`/`vector_t` types used
across both movement systems and the geometry classes.
