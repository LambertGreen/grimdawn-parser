#!/bin/bash

output_dir="grimdawn_decoded"
minified_dir="$output_dir/minified"
mkdir -p "$minified_dir" # Create directory for minified files

# Counter for file naming
counter=1

# Loop through each JSON file safely, even if filenames contain spaces
find "$output_dir" -name "*.json" -print0 | while IFS= read -r -d '' file; do
    # Create a minified version of each file
    min_file="$minified_dir/player$counter.min.json"
    jq '{"player-data": {"bio": .["player-data"].bio, "stats": .["player-data"].stats}, "player-name": ."player-name"}' "$file" > "$min_file"
    ((counter++))
done

# Combine all minified files into a single array in one file
jq -s '.' "$minified_dir"/*.min.json > "$output_dir/all-characters-combined.json"
