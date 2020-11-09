mkdir build
cmake --no-warn-unused-cli -DCMAKE_TOOLCHAIN_FILE=cmake/arm-gcc-toolchain.cmake -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -H. -B./build -G Ninja