#!/bin/bash

# Script to create a filtered version of each player.json file
# Usage: ./filter_player_json.sh <players_directory> <output_directory>

players_dir="$1"
out_dir="$2"
filter_script="./scripts/filter_player.jq"

# Using find to locate all .json files in the source directory
find "$players_dir" -name "*.json" -print0 | while IFS= read -r -d '' file; do

    # Replacing the source directory path with the target directory path in each found file's path
    target_file="${file//$players_dir/$out_dir}"

    mkdir -p "$(dirname "$target_file")"
    echo "Filtering \"$file\" to \"$target_file\"..."
    cmd="jq -f \"$filter_script\" \"$file\" > \"$target_file\""
    echo "Running: $cmd"
    eval "$cmd"
done
