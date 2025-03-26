#!/bin/bash

# Color definitions
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
RESET='\033[0m'

# Path to push_swap and checker_OS executables
PUSH_SWAP="../push_swap"
CHECKER="./checker_OS"

# Function to generate random numbers
generate_random_numbers() {
    local size=$1
    local numbers=()
    local i=0

    while [ $i -lt $size ]; do
        # Generate a random number between -1000 and 1000
        random_num=$((RANDOM % 2001 - 1000))
        
        # Check if the number is already in the array
        if [[ ! " ${numbers[@]} " =~ " ${random_num} " ]]; then
            numbers+=($random_num)
            ((i++))
        fi
    done
    
    echo "${numbers[@]}"
}

# Function to run a test
run_test() {
    local test_name=$1
    local numbers=$2
    local expected_result=$3
    
    echo -e "${YELLOW}Running test: ${test_name}${RESET}"
    echo -e "${BLUE}Input: ${numbers}${RESET}"
    
    # Run push_swap and count operations
    local operations=$($PUSH_SWAP $numbers | wc -l)
    
    # Run checker_OS to verify the sort is correct
    local sort_result=$($PUSH_SWAP $numbers | $CHECKER $numbers)
    
    if [ "$sort_result" == "OK" ]; then
        echo -e "${GREEN}Sort result: OK${RESET}"
    else
        echo -e "${RED}Sort result: KO${RESET}"
    fi
    
    echo -e "${BLUE}Operation count: ${operations}${RESET}"
    
    if [ "$expected_result" != "" ] && [ $operations -gt $expected_result ]; then
        echo -e "${RED}Too many operations! Expected <= ${expected_result}${RESET}"
    else
        echo -e "${GREEN}Operation count is good!${RESET}"
    fi
    
    echo ""
}

# Check if the executables exist
if [ ! -f "$PUSH_SWAP" ]; then
    echo -e "${RED}Error: push_swap executable not found at ${PUSH_SWAP}${RESET}"
    exit 1
fi

if [ ! -f "$CHECKER" ]; then
    echo -e "${YELLOW}Warning: checker_OS not found at ${CHECKER}. Skipping sort verification.${RESET}"
    CHECKER="echo"
fi

# Basic tests
echo -e "${GREEN}=== BASIC TESTS ===${RESET}"

# Test with already sorted array
run_test "Already sorted" "1 2 3 4 5" 0

# Test with reverse sorted array
run_test "Reverse sorted" "5 4 3 2 1" 12

# Test with 3 numbers
run_test "3 numbers" "2 1 3" 2

# Random tests
echo -e "${GREEN}=== RANDOM TESTS ===${RESET}"

# Test with 5 random numbers
numbers=$(generate_random_numbers 5)
run_test "5 random numbers" "$numbers" 12

# Test with 100 random numbers (if available)
if [ "$1" == "full" ]; then
    numbers=$(generate_random_numbers 100)
    run_test "100 random numbers" "$numbers" 700
    
    numbers=$(generate_random_numbers 500)
    run_test "500 random numbers" "$numbers" 5500
else
    echo -e "${YELLOW}Skipping large tests. Run with 'full' argument to include them.${RESET}"
fi

echo -e "${GREEN}Tests completed!${RESET}"