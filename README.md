# civ-andreas

## Building

### SPDLOG

SPDLOG is used for logging in the project, and must be build before building the main application.

```
cd ext/spdlog
mkdir build && cd build
cmake .. && cmake --build . --target all
```
