#!/bin/bash

# Script to create a filtered version of each player.json file
# Usage: ./filter_player_json.sh <players_directory> <output_directory>

players_dir="$1"
db_file="$2"

# Use find to locate all .json files in the source directory
find "$players_dir" -name "*.json" -print0 | while IFS= read -r -d '' file; do

    echo "Importing \"$file\" to \"$db_file\"..."
    cmd="python ./scripts/import_player_json_to_postgres_db.py \"$file\" \"$db_file\""
    echo "Running: $cmd"
    eval "$cmd"
done
