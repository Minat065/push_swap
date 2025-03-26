#!/bin/bash

# Color definitions
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
RESET='\033[0m'

# Path to push_swap executable
PUSH_SWAP="../push_swap"

# Directory for storing logs
LOG_DIR="valgrind_logs"
mkdir -p $LOG_DIR

# Valgrind options
VALGRIND_OPTS="--leak-check=full --show-leak-kinds=all --track-origins=yes"

# Function to run a valgrind test
run_valgrind_test() {
    local test_name=$1
    local numbers=$2
    local log_file="${LOG_DIR}/${test_name}.log"
    
    echo -e "${YELLOW}Running Valgrind test: ${test_name}${RESET}"
    echo -e "${BLUE}Input: ${numbers}${RESET}"
    
    # Run valgrind
    valgrind $VALGRIND_OPTS $PUSH_SWAP $numbers 2> $log_file
    
    # Check if there were any memory leaks
    if grep -q "no leaks are possible" $log_file; then
        echo -e "${GREEN}No memory leaks detected!${RESET}"
    else
        echo -e "${RED}Memory leaks detected! Check ${log_file} for details.${RESET}"
        grep -A 2 "LEAK SUMMARY" $log_file
    fi
    
    # Check for other memory errors
    if grep -q "ERROR SUMMARY: 0 errors" $log_file; then
        echo -e "${GREEN}No memory errors detected!${RESET}"
    else
        echo -e "${RED}Memory errors detected! Check ${log_file} for details.${RESET}"
        grep -A 2 "ERROR SUMMARY" $log_file
    fi
    
    echo ""
}

# Check if the executable exists
if [ ! -f "$PUSH_SWAP" ]; then
    echo -e "${RED}Error: push_swap executable not found at ${PUSH_SWAP}${RESET}"
    exit 1
fi

# Test with different inputs
echo -e "${GREEN}=== VALGRIND MEMORY TESTS ===${RESET}"

# Empty input
run_valgrind_test "empty" ""

# Single number
run_valgrind_test "single" "42"

# Already sorted small set
run_valgrind_test "sorted_small" "1 2 3 4 5"

# Reverse sorted small set
run_valgrind_test "reverse_small" "5 4 3 2 1"

# Small random set
run_valgrind_test "random_small" "4 2 8 5 1"

# Error case - duplicate
run_valgrind_test "error_duplicate" "1 2 3 2 4"

# Error case - non-integer
run_valgrind_test "error_non_integer" "1 2 three 4"

# Error case - out of range
run_valgrind_test "error_out_of_range" "2147483647 2147483648"

# Medium set (if time permits)
if [ "$1" == "full" ]; then
    # Generate a random set of 50 numbers
    MEDIUM_SET=$(python3 ../generate_random.py 50)
    run_valgrind_test "medium" "$MEDIUM_SET"
    
    # Generate a random set of 100 numbers (for brief testing)
    LARGE_SET=$(python3 ../generate_random.py 100)
    run_valgrind_test "large" "$LARGE_SET"
else
    echo -e "${YELLOW}Skipping larger tests. Run with 'full' argument to include them.${RESET}"
fi

echo -e "${GREEN}Valgrind tests completed!${RESET}"
echo -e "${BLUE}Logs saved in ${LOG_DIR}/${RESET}"

# Summary
echo -e "${GREEN}=== SUMMARY ===${RESET}"
echo -e "Total tests run: $(ls $LOG_DIR | wc -l)"
echo -e "Tests with memory leaks: $(grep -l "definitely lost" $LOG_DIR/* | wc -l)"
echo -e "Tests with memory errors: $(grep -l "ERROR SUMMARY: [^0]" $LOG_DIR/* | wc -l)"