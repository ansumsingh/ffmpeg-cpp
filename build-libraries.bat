mkdir build

cmake -s . -B build -DCMAKE_TOOLCHAIN_FILE=%CD%\dependencies\vcpkg\scripts\buildsystems\vcpkg.cmake

cmake --build build