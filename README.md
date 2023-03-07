# Civilization Andreas

## Dependencies

The project relies on three dependencies, which must all be placed in `ext`.

1. `glew`
    Download from https://glew.sourceforge.net/. Unzip and place the files in `ext/glew`.

2. `glfw`
    Download latest release from https://www.glfw.org/. Unzip and place the files in `ext/glfw`.
    The path to the `CMakeLists.txt` should be `ext/glfw/CMakeLists.txt`.


## Building

Currently only `CMake Ninja` together with `MSYS2` has been tested.

To build, run the following command in `civ-andreas/build`:

```
cmake .. -G Ninja
```
