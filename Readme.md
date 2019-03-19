This repository provides a reproduction for LTO issue in GNU MCU Eclipse GCC toolchain.

# Steps

1. Clone this repository to `<Work>/src` folder
2. Create directory for build: `mkdir <Work>/build`
3. Generate CMake build: `cd <Work>/build && cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -DENABLE_LTO=ON -DTOOLCHAIN=<toolchain_directory>/bin <Work>/src`
4. Run build: `make app.dump_bin`
5. Check size for resulting binary: `ls -l <Work>/bin/app/app.bin`

# Expected Result

`app.bin` should be around 1600 bytes

# Actual Result

`app.bin` is around 3000 bytes and is binary identical to version without LTO.
