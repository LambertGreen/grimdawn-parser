#!/bin/bash

# Script to combine each player.json file into a single json file
# Usage: ./combine_player_info.sh <players_directory> <output_directory>

players_dir="$1"
out_file="$2"

mkdir -p "$(dirname "$out_file")"
echo "Combining files into \"$out_file\""
cmd="jq -s '.' \"$players_dir\"/*/*.json > \"$out_file\""
echo "Running: $cmd"
eval "$cmd"
