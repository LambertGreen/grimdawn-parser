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
  @echo "Cleaning test ouput..."
  trash test_output

#-------------------------------------------------------------------------------
# Debugging
#-------------------------------------------------------------------------------
# debug with lldb
debug:
  lldb ./build/grimparse -- \
    --action export-json \
    --file testfiles/_Thor/player.gdc \
    --name Thor \
    --file-out test_output/exported_json/_Thor/player.json

#-------------------------------------------------------------------------------
# Testing
#-------------------------------------------------------------------------------
# test all
test: test-single test-multi

# test againgst a single file
test-single: build \
  test-export-single \
  test-edit-single \
  test-edit-reset-single \
  test-filter-single

# test against multiple files
test-multi: build \
  test-export-multi \
  test-edit-multi \
  test-edit-reset-multi \
  test-filter-multi \
  test-combine

# Testing - Exporting
#-------------------------------------------------------------------------------
# test export a single player
test-export-single:
  @echo "Running test-export-single..."
  mkdir -p test_output/exported_single/_Thor
  ./build/grimparse --action export-json \
                    --file testfiles/_Thor/player.gdc \
                    --name Thor \
                    --file-out test_output/exported_single/_Thor/player.json

# test export on multiple players
test-export-multi:
  @echo "Running test-export-multi..."
  ./scripts/decode_players_info.sh ./testfiles ./test_output/exported_multi

# Testing - Editing
#-------------------------------------------------------------------------------
# test edit action on single player
test-edit-single:
  @echo "Running test-edit-single..."
  mkdir -p test_output/edited_single/_Thor
  ./build/grimparse --action edit \
                    --file testfiles/_Thor/player.gdc \
                    --edit-action "none" \
                    --file-out test_output/edited_single/_Thor/player.gdc

# test edit action on multiple players
test-edit-multi:
  @echo "Running test-edit-multi..."
  ./scripts/edit_players_info.sh ./testfiles none ./test_output/edited_multi

# Testing - Editing - reset stats
#-------------------------------------------------------------------------------
# test edit action reset on single player
test-edit-reset-single:
  @echo "Running test-edit-reset-single..."
  mkdir -p test_output/edited_reset_stats_single/_Thor
  ./build/grimparse --action edit \
                    --file testfiles/_Thor/player.gdc \
                    --edit-action "reset-stats" \
                    --file-out test_output/edited_reset_stats_single/_Thor/player.gdc

# test edit action reset on multiple players
test-edit-reset-multi:
  @echo "Running test-edit-reset-multi..."
  ./scripts/edit_players_info.sh ./testfiles reset-stats ./test_output/edited_reset_stats_multi

# Testing - Filter player info
#-------------------------------------------------------------------------------
# test filter single player
test-filter-single: test-export-single
  mkdir -p test_output/filtered_single/_Thor
  jq -f ./scripts/filter_player.jq \
        test_output/exported_single/_Thor/player.json > \
          test_output/filtered_single/_Thor/player.json

# test filter multiple players
test-filter-multi: test-export-multi
  ./scripts/filter_players_json.sh ./test_output/exported_multi ./test_output/filtered_multi

# Testing - Combine player info
#-------------------------------------------------------------------------------
# test combine filtered player json files
test-combine: test-filter-multi
  ./scripts/combine_players_json.sh ./test_output/filtered_multi ./test_output/all-characters.json

#-------------------------------------------------------------------------------
# Runs
#-------------------------------------------------------------------------------
# run decode player.gdc files
run-export-players:
  @echo "Running export of player.gdc files..."
  ./scripts/decode_players_info.sh ./grimdawn_save ./processed/exported

# run filter on player.json files
run-filter-players:
  @echo "Running filtering of player.json files..."
  ./scripts/filter_players_json.sh ./processed/exported ./processed/filtered

# run combine player.json files
run-combine-players:
  @echo "Running combining of player.json files..."
  ./scripts/combine_players_json.sh ./processed/filtered ./processed/combined/players.json

# run all
run: \
  run-export-players \
  run-filter-players \
  run-combine-players

# Edit reset player stats
run-edit-reset-player-stats:
  @echo "Running reseting of player stats..."
  ./scripts/edit_players_info.sh ./grimdawn_save reset-stats ./processed/edited_reset_stats

# Copy edited player.gdc files to GrimDawn save directory
run-copy-edited-files-to-save-dir:
  @echo "Copying edited files to GrimDawn save directory..."
  ./scripts/copy_player_files.sh ./processed/edited_reset_stats ./grimdawn_save/main

run-create-players-db:
  @echo "Creating grimdawn players DB.."
  createdb -U lgreen grimdawn_players

run-import-players-to-db:
  @echo "Importing player json files into players DB..."
  ./scripts/import_players_to_db.sh processed/filtered "dbname='grimdawn_players' user='lgreen' host='localhost'"
