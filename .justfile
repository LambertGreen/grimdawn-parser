# -*- mode: makefile -*-

set dotenv-load

# default
default:
  just --list -u

#-------------------------------------------------------------------------------
# Formatting
#-------------------------------------------------------------------------------
# format
format:
	find src -iname '*.cpp' -o -iname '*.hpp' | xargs clang-format -i

#-------------------------------------------------------------------------------
# Building
#-------------------------------------------------------------------------------
# generate with cmake
generate:
	cmake -Bbuild -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_BUILD_TYPE=Debug -G Ninja

# build with cmake
build:
	cmake --build build

# clean build
clean:
	trash build

# debug with lldb
debug:
	lldb ./build/grimparse -- --action export-json --file testfiles/_Thor/player.gdc --name Thor --file-out testfiles/_Thor/player.json

#-------------------------------------------------------------------------------
# Tests
#-------------------------------------------------------------------------------
# test
test: test-export

# test export
test-export: test-export-thor

# test export player Iska
test-export-iska:
	./build/grimparse --action export-json --file testfiles/_Iska/player.gdc --name Iska --file-out testfiles/_Iska/player.json

# test export player Luna
test-export-luna:
	./build/grimparse --action export-json --file testfiles/_Luna/player.gdc --name Luna --file-out testfiles/_Luna/player.json

# test export player Luthar
test-export-luthar:
	./build/grimparse --action export-json --file testfiles/_Luthar/player.gdc --name Luthar --file-out testfiles/_Luthar/player.json

# test export player Thor
test-export-thor:
	./build/grimparse --action export-json --file testfiles/_Thor/player.gdc --name Thor --file-out testfiles/_Thor/player.json

# test export on all players
test-export-all: test-export-iska test-export-luna test-export-luthar test-export-thor

# combine all players
test-combine:
    jq -s '.' \
       testfiles/_Iska/player.json      \
       testfiles/_Luna/player.json      \
       testfiles/_Luthar/player.json    \
       testfiles/_Thor/player.json      \
       > testfiles/combined.json

#-------------------------------------------------------------------------------
# Runs
#-------------------------------------------------------------------------------
# run decode player.gdc files
run-export-player:
	./scripts/decode_player_info.sh

# run combine player.json files
run-combine:
	./scripts/combine_player_info.sh
