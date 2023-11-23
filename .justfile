# -*- mode: makefile -*-

# generate with cmake
generate:
	cmake -Bbuild -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

# build with make
build:
	cd build && make

# debug with lldb
debug:
	lldb ./grimparse testfiles/player.gdc

# debug with gdb
debug_with_gdb:
    gdb -- ./grimparse testfiles/player.gdc

# run
test:
	./build/grimparse testfiles/_Thor/player.gdc Thor > testfiles/_Thor/player.json

# run on player Iska
test-iska:
	./build/grimparse testfiles/_Iska/player.gdc Iska > testfiles/_Iska/player.json

# run on player Luna
test-luna:
	./build/grimparse testfiles/_Luna/player.gdc Luna > testfiles/_Luna/player.json

# run on player Luthar
test-luthar:
	./build/grimparse testfiles/_Luthar/player.gdc Luthar > testfiles/_Luthar/player.json

# run on player Thor
test-thor:
	./build/grimparse testfiles/_Thor/player.gdc Thor > testfiles/_Thor/player.json

# run on all players
test-all: run-iska run-luna run-luthar run-thor

# combine all players
test-combine:
    jq -s '.' \
       testfiles/_Iska/player.json      \
       testfiles/_Luna/player.json      \
       testfiles/_Luthar/player.json    \
       testfiles/_Thor/player.json      \
       > testfiles/combined.json

# clean
clean:
	trash build
