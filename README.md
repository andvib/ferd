# Ferd

## Building the Project

### Setup

1. Clone the repository with submodules:
```bash
git clone https://github.com/andvib/ferd
cd ferd
git submodule init
git submodule update
```

2. Download and install GLEW:
```bash
curl -L -o glew.zip https://sourceforge.net/projects/glew/files/glew/2.1.0/glew-2.1.0-win32.zip
unzip glew.zip -d ext/
mv ext/glew-2.1.0 ext/glew
```

3. Download and install GLFW (if not using system version):
```bash
curl -L -o glfw.zip https://github.com/glfw/glfw/releases/download/3.4/glfw-3.4.zip
unzip glfw.zip -d ext/
mv ext/glfw-3.4 ext/glfw
```

### Building with CMake

#### Build the main executable:
```bash
mkdir build
cd build
cmake .. -DBUILD_FERD=ON
cmake --build .
```

#### Build with tests:
```bash
mkdir build
cd build
cmake .. -DBUILD_FERD=ON -DBUILD_TESTS=ON
cmake --build .
ctest
```

#### Using MinGW for Windows cross-compilation:
```bash
export CXX=/usr/bin/x86_64-w64-mingw32-g++
export CC=/usr/bin/x86_64-w64-mingw32-gcc
mkdir build
cd build
cmake .. -DBUILD_FERD=ON -G Ninja
ninja
```

### Building with Docker

A Dockerfile is provided for a complete build environment:

```bash
docker build -t ferd-builder .
docker run -v $(pwd):/output ferd-builder
```

### CMake Build Options

- `BUILD_FERD` - Build the Ferd executable (default: OFF)
- `BUILD_TESTS` - Build the test suite (default: OFF)

## Sources

Sources used for this project:

- [An Introduction To Modern CMake](https://cliutils.gitlab.io/modern-cmake/)