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
	./build/grimparse testfiles/_Thor/player.gdc Thor > testfiles/_Thor/player.json

# run on player Iska
run-iska:
	./build/grimparse testfiles/_Iska/player.gdc Iska > testfiles/_Iska/player.json

# run on player Luna
run-luna:
	./build/grimparse testfiles/_Luna/player.gdc Luna > testfiles/_Luna/player.json

# run on player Luthar
run-luthar:
	./build/grimparse testfiles/_Luthar/player.gdc Luthar > testfiles/_Luthar/player.json

# run on player Thor
run-thor:
	./build/grimparse testfiles/_Thor/player.gdc Thor > testfiles/_Thor/player.json

# run on all players
run-all: run-iska run-luna run-luthar run-thor

# combine all players
combine:
    jq -s '.' \
       testfiles/_Iska/player.json      \
       testfiles/_Luna/player.json      \
       testfiles/_Luthar/player.json    \
       testfiles/_Thor/player.json      \
       > testfiles/combined.json

# clean
clean:
	trash build
