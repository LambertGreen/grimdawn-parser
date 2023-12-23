#!/usr/bin/env sh

# Directory paths
input_dir="grimdawn_save"
output_dir="grimdawn_decoded"

# Create output directory if it doesn't exist
mkdir -p "$output_dir"

# Process each player.gdc file
find "$input_dir" -name "player.gdc" | while IFS= read -r file; do
    # Extract character name
    character_name=$(basename "$(dirname "$file")")
    character_name=${character_name#_} # Remove leading underscore if present
    echo "Decoding $file $character_name"

    # Create directory for decoded files
    mkdir -p "$output_dir/$character_name"

    # Call decryption tool (replace 'your_decryption_tool' with the actual tool's name)
    build/grimparse --action export-json --file "$file"  --name "$character_name" --file-out "$output_dir/$character_name/player.json"
done

