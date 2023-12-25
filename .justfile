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
	lldb ./build/grimparse -- --action export-json --file testfiles/_Thor/player.gdc --name Thor --file-out testfiles/_Thor/player.json

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
test-export-all: build test-export-iska test-export-luna test-export-luthar test-export-thor

# test edit action
test-edit: test-edit-thor

# test edit action on player thor
test-edit-thor:
  build/grimparse --action edit --file testfiles/_Thor/player.gdc --edit-action "none" --file-out testfiles/_Thor/player.out.g

# test edit action on player iska
test-edit-iska:
  build/grimparse --action edit --file testfiles/_Iska/player.gdc --edit-action "none" --file-out testfiles/_Iska/player.out.g

# test edit action reset on player thor
test-edit-reset-thor: test-setup
  build/grimparse --action edit --file testfiles/_Thor/player.gdc --edit-action "reset-stats" --file-out testfiles/_Thor/player.reset.out.g

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
