#!/usr/bin/env sh

build_dir="build"
grimparse="$build_dir/grimparse"
input_dir="grimdawn_save"
output_dir="grimdawn_decoded"

# Decode each player.gdc file
find "$input_dir" -name "player.gdc" | while IFS= read -r file; do
    # Extract character name
    character_name=$(basename "$(dirname "$file")")

    # Remove leading underscore from directory name
    character_name=${character_name#_}

    echo "Decoding $file $character_name"

    # Create directory for decoded files
    mkdir -p "$output_dir/$character_name"

    # Decode player.gdc file into player.json file
    cmd="$grimparse --action export-json --file \"$file\"  --name \"$character_name\" --file-out $output_dir/\"$character_name\"/player.json"
    echo "Running: $cmd"
    eval "$cmd"
done
