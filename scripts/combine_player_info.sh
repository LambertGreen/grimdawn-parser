#!/bin/bash

output_dir="grimdawn_decoded"
minified_dir="$output_dir/minified"
minify_script="./scripts/minify.jq"
combined_json="$output_dir/all-characters-combined.json"

# Create directory for minified files
mkdir -p "$minified_dir"

# Counter for file naming
counter=0

# Create a minified version of each player.json file
find "$output_dir" -name "*.json" -print0 | while IFS= read -r -d '' file; do

    ((counter++))
    min_file="$minified_dir/player$counter.min.json"
    echo "Minifying \"$file\" to \"$min_file\..."
    cmd="jq -f \"$minify_script\" \"$file\" > \"$min_file\""
    echo "Running: $cmd"
    eval "$cmd"
done

# Combine all minified files into a single array in one file
echo "Combining minified files into \"$combined_json\""
cmd="jq -s '.' \"$minified_dir\"/*.min.json > \"$combined_json\""
echo "Running: $cmd"
eval "$cmd"
