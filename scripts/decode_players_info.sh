#!/bin/bash

# Script to decode Grim Dawn player.gdc file into a JSON file
# Usage: ./decode_player_info.sh <players_directory> <output_directory>

players_dir="$1"
output_dir="$2"
build_dir="build"
grimparse="$build_dir/grimparse"

# Use find to locate all player.gdc files in the source directory
find "$players_dir" -name "player.gdc" | while IFS= read -r file; do
    character_dir=$(basename "$(dirname "$file")")

    # Remove leading underscore from directory name
    character_name=${character_dir#_}

    echo "Decoding $file"

    # Create directory for decoded files
    mkdir -p "$output_dir/$character_dir"

    # Decode player.gdc file into player.json file
    cmd="$grimparse --action export-json --file \"$file\"  --name \"$character_name\" --file-out $output_dir/\"$character_dir\"/player.json"
    echo "Running: $cmd"
    eval "$cmd"
done
