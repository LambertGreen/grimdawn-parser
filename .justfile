# build with clang
build:
    clang++ -g -O0 -std=c++17 -o grimparse decrypt.cpp

# build with g++
build_with_gnu:
	g++ decrypt.cpp -std=c++17 -o grimparse

# debug with lldb
debug:
	lldb ./grimparse testfiles/player.gdc output.txt

# debug with gdb
debug_with_gdb:
    gdb -- ./grimparse testfiles/player.gdc output.txt

# run
run:
	./grimparse testfiles/player.gdc output.txt
