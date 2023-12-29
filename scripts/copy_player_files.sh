#!/bin/bash

# Script to edit Grim Dawn player.gdc file
# Usage: ./copy_player_files.sh. <players_directory>  <dest_directory>
#
source_dir="$1"
destination_dir="$2"

# Loop through the source directory
find "$source_dir" -type f -name "player.gdc" | while read -r src_file; do
    # Extract player name from the path
    player_name=$(basename "$(dirname "$src_file")")

    # Define destination file path
    dest_file="$destination_dir/$player_name/player.gdc"

    # Ensure the destination directory exists
    mkdir -p "$(dirname "$dest_file")"

    # Copy the file
    cmd="cp -f \"$src_file\" \"$dest_file\""
    echo "Running: $cmd"
    eval "$cmd"
done
