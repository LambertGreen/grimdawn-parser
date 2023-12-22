# -*- mode: makefile -*-

# default
default: build

# format
format:
	find src -iname '*.cpp' -o -iname '*.hpp' | xargs clang-format -i

# generate with cmake
#
generate:
	cmake -Bbuild -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_BUILD_TYPE=Debug -G Ninja

# build with cmake
build:
	cmake --build build

# debug with lldb
debug:
	lldb ./build/grimparse --action export-json --file testfiles/_Thor/player.gdc --name Thor --file-out testfiles/_Thor/player.json

# debug with gdb
debug_with_gdb:
    gdb -- ./build/grimparse --action export-json --file testfiles/_Thor/player.gdc --name Thor

# run
test:
	./build/grimparse --action export-json --file testfiles/_Thor/player.gdc --name Thor --file-out testfiles/_Thor/player.json

# run on player Iska
test-iska:
	./build/grimparse --action export-json --file testfiles/_Iska/player.gdc --name Iska --file-out testfiles/_Iska/player.json

# run on player Luna
test-luna:
	./build/grimparse --action export-json --file testfiles/_Luna/player.gdc --name Luna --file-out testfiles/_Luna/player.json

# run on player Luthar
test-luthar:
	./build/grimparse --action export-json --file testfiles/_Luthar/player.gdc --name Luthar --file-out testfiles/_Luthar/player.json

# run on player Thor
test-thor:
	./build/grimparse --action export-json --file testfiles/_Thor/player.gdc --name Thor --file-out testfiles/_Thor/player.json

# run on all players
test-all: test-iska test-luna test-luthar test-thor

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
	trash grimdawn_decoded

# decode player.gdc --name files
decode:
	./scripts/decode_player_info.sh

# combine player.json files
combine:
	./scripts/combine_player_info.sh
