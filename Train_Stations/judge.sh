#!/bin/bash

program="./train.out"
test_dir="./Tests"

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

temp_dir=$(mktemp -d)

echo "Building the project..."
make

if [ $? -ne 0 ]; then
    echo -e "${RED}Build failed. Aborting tests.${NC}"
    rm -rf "$temp_dir"
    exit 1
fi

find "$test_dir" -type f -name "*.in" | while read -r input_file; do
    expected_output="${input_file%.in}.out"
    
    result_output="$temp_dir/$(basename "${input_file%.in}.out")"
    
    $program < "$input_file" > "$result_output"
    
    if diff -q -w "$result_output" "$expected_output" > /dev/null; then
        echo -e "${GREEN}PASS: $(basename "$input_file")${NC}"
    else
        echo -e "${RED}FAIL: $input_file${NC}"
    fi
done

rm -rf "$temp_dir"

