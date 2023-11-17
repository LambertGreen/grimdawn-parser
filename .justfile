# generate with cmake
generate:
	cmake -Bbuild -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

# build with make
build:
	cd build && make

# build with clang
build_with_clang:
    clang++ -g -O0 -std=c++17 -o grimparse decrypt.cpp

# build with g++
build_with_gnu:
	g++ decrypt.cpp -std=c++17 -o grimparse

# debug with lldb
debug:
	lldb ./grimparse testfiles/player.gdc

# debug with gdb
debug_with_gdb:
    gdb -- ./grimparse testfiles/player.gdc

# run
run:
	./build/grimparse testfiles/player.gdc > player.json

# clean
clean:
	trash build
