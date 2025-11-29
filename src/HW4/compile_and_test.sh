cmake -S . -B build
cmake --build build
cd build && ctest
# ./build/bin/main