#===============================================================================
# Project Justfile
# - for building, testing, and command execution
# - use with https://github.com/casey/just
#===============================================================================

# load the project .env file
set dotenv-load

# default
default:
  @just --list -u

#-------------------------------------------------------------------------------
# Aliases
#-------------------------------------------------------------------------------
alias f := format
alias g := generate
alias b := build
alias c := clean
alias t := test

# Formatting
#-------------------------------------------------------------------------------
# format
format:
  @echo "Formatting code files..."
  find src -iname '*.cpp' -o -iname '*.hpp' | xargs clang-format -i

#-------------------------------------------------------------------------------
# Building
#-------------------------------------------------------------------------------
# generate with cmake
generate:
  @echo "Generating build system..."
  cmake -Bbuild -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_BUILD_TYPE=Debug -G Ninja

# build with cmake
build: generate format
  @echo "Building..."
  cmake --build build

# clean build
clean:
  @echo "Cleaning build..."
  trash build

#-------------------------------------------------------------------------------
# Debugging
#-------------------------------------------------------------------------------
# debug with lldb
debug:
	lldb ./build/grimparse -- --action export-json --file testfiles/_Thor/player.gdc --name Thor --file-out out/testfiles_json/_Thor/player.json

#-------------------------------------------------------------------------------
# Testing
#-------------------------------------------------------------------------------
# test setup
test-setup: build
  @echo "Running tests..."

# test
test: test-setup test-export test-edit

# test export
test-export: test-export-thor

# test export player Iska
test-export-iska:
  mkdir -p out/testfiles_json/_Iska
  ./build/grimparse --action export-json --file testfiles/_Iska/player.gdc --name Iska --file-out out/testfiles_json/_Iska/player.json

# test export player Luna
test-export-luna:
  mkdir -p out/testfiles_json/_Luna
  ./build/grimparse --action export-json --file testfiles/_Luna/player.gdc --name Luna --file-out out/testfiles_json/_Luna/player.json

# test export player Luthar
test-export-luthar:
  mkdir -p out/testfiles_json/_Luthar
  ./build/grimparse --action export-json --file testfiles/_Luthar/player.gdc --name Luthar --file-out out/testfiles_json/_Luthar/player.json

# test export player Thor
test-export-thor:
  mkdir -p out/testfiles_json/_Thor
  ./build/grimparse --action export-json --file testfiles/_Thor/player.gdc --name Thor --file-out out/testfiles_json/_Thor/player.json

# test export on all players
test-export-all: build test-export-iska test-export-luna test-export-luthar test-export-thor

# test edit action
test-edit: test-edit-thor

# test edit action on player thor
test-edit-thor:
  ./build/grimparse --action edit --file testfiles/_Thor/player.gdc --edit-action "none" --file-out out/testfiles_json/_Thor/player.g

# test edit action on player iska
test-edit-iska:
  ./build/grimparse --action edit --file testfiles/_Iska/player.gdc --edit-action "none" --file-out out/testfiles_json/_Iska/player.g

# test edit action reset on player thor
test-edit-reset-thor: test-setup
  ./build/grimparse --action edit --file testfiles/_Thor/player.gdc --edit-action "reset-stats" --file-out out/testfiles_json/_Thor/player.reset.g

# test filter players
test-filter:
  ./scripts/filter_player_json.sh ./out/testfiles_json ./out/testfiles_filtered_json

# test combinne filtered player json files
test-combine: test-filter
  ./scripts/combine_player_info.sh ./out/testfiles_filtered_json ./out/testfiles_combined/all-characters.json

#-------------------------------------------------------------------------------
# Tests for importing player json files into a MongoDB
#-------------------------------------------------------------------------------
# test import into MongoDB, player Iska
test-mongo-import-iska:
  mongoimport --db GrimDawn --collection PlayerInfoTest --file ./testfiles/_Iska/player.json

# test import into MongoDB, player Luna
test-mongo-import-luna:
  mongoimport --db GrimDawn --collection PlayerInfoTest --file ./testfiles/_Luna/player.json

# test import into MongoDB, player Luthar
test-mongo-import-luthar:
  mongoimport --db GrimDawn --collection PlayerInfoTest --file ./testfiles/_Luthar/player.json

# test import into MongoDB, player Thor
test-mongo-import-thor:
  mongoimport --db GrimDawn --collection PlayerInfoTest --file ./testfiles/_Thor/player.json

# test import into MongoDB, all players
test-mongo-import-all: test-mongo-import-iska test-mongo-import-luna test-mongo-import-luthar test-mongo-import-thor

#-------------------------------------------------------------------------------
# Runs
#-------------------------------------------------------------------------------
# run decode player.gdc files
run-export-player:
	./scripts/decode_player_info.sh

# run combine player.json files
run-combine:
	./scripts/combine_player_info.sh
