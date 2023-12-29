#!/bin/bash

# Script to edit Grim Dawn player.gdc file
# Usage: ./edit_player_info.sh <players_directory> <edit_action> <output_directory>

players_dir="$1"
edit_action="$2"
output_dir="$3"
build_dir="build"
grimparse="$build_dir/grimparse"

# Use find to locate all player.gdc files in the source directory
find "$players_dir" -name "player.gdc" | while IFS= read -r file; do
    character_dir=$(basename "$(dirname "$file")")
    echo "Decoding $file"
    mkdir -p "$output_dir/$character_dir"
    cmd="$grimparse --action edit --file \"$file\" --edit-action \"$edit_action\" --file-out $output_dir/\"$character_dir\"/player.gdc"
    echo "Running: $cmd"
    eval "$cmd"
done
