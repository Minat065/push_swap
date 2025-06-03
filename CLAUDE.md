# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is a **push_swap** project - a 42 School assignment that implements sorting algorithms using two stacks with limited operations. The goal is to sort integers using the minimum number of operations.

### Assignment Requirements (from subject.md)

- Sort integers in stack A in ascending order using only specific operations
- Stack A starts with random unique integers, stack B starts empty
- Must display the shortest sequence of operations to sort the stack
- Performance benchmarks:
  - 3 numbers: ≤ 3 operations
  - 5 numbers: ≤ 12 operations  
  - 100 numbers: < 700 operations (for 100% grade)
  - 500 numbers: < 5500 operations (for 100% grade)

### Allowed Operations

- `sa`/`sb`: Swap first 2 elements of stack A/B
- `ss`: sa and sb simultaneously
- `pa`/`pb`: Push top element from B to A / A to B
- `ra`/`rb`: Rotate stack (first element becomes last)
- `rr`: ra and rb simultaneously
- `rra`/`rrb`: Reverse rotate (last element becomes first)
- `rrr`: rra and rrb simultaneously

## Build Commands

```bash
make         # Build push_swap executable
make test    # Build test executable for unit tests
make clean   # Remove object files
make fclean  # Remove all built files including executables
make re      # Clean and rebuild everything
make valgrind # Run valgrind memory leak check on push_swap
```

## Testing Commands

```bash
# Run comprehensive test suite
./test.sh

# Build and run unit tests
make test
./test_push_swap

# Test with specific numbers
./push_swap 3 2 1 5 4

# Validate operations with checker
./push_swap 3 2 1 | ./checker_linux 3 2 1

# Generate and test random numbers
ARG=$(python3 -c "import random; print(' '.join(map(str, random.sample(range(-1000, 1000), 100))))"); ./push_swap $ARG | ./checker_linux $ARG
```

## Architecture

The codebase implements a stack-based sorting system with two main components:

1. **Stack Operations Layer** (`src/operations/`, `src/stack_basic/`)
   - Implements the allowed operations: sa, sb, pa, pb, ra, rb, rra, rrb
   - Each operation manipulates one or both stacks according to strict rules

2. **Sorting Algorithm Layer** (`src/sort/`)
   - Different sorting strategies based on input size:
     - Size 2: Direct comparison and swap (`sort_two()`)
     - Size 3: Hardcoded optimal solution (`sort_three()`)
     - Size 4-5: Uses auxiliary stack B with targeted sorting (`sort_four()`, `sort_five()`)
     - Size 6-100: Optimized chunk-based sorting (`optimized_sort()`)
     - Size 101-200: Optimized chunk-based sorting with adjusted chunk sizes
     - Size 200-350: Alternative chunk sorting (`chunk_sort()`)
     - Size 351-500: Optimized chunk-based sorting with larger chunks
     - Size > 500: Radix sort implementation (`radix_sort()`)

The sorting strategy is selected in `src/sort/push_swap.c` based on the stack size. All sorting algorithms (except for size 2-5) first normalize values to consecutive ranks (0, 1, 2, ...) using `rank_normalize()` to simplify operations.

## Key Implementation Details

- **Input Validation**: All inputs are validated for integer range, duplicates, and format in `src/utils/validate_input.c`
- **Memory Management**: Uses custom libft library for all allocations, with proper cleanup on exit
- **Operation Output**: Each operation prints its name to stdout (e.g., "sa\n", "pb\n")
- **Error Handling**: Prints "Error\n" to stderr for any invalid input
- **Main Sorting Algorithms**:
  - `optimized_sort.c`: Chunk-based sorting with adaptive chunk sizes (18 for ≤100, 25 for ≤200, 70 for ≤500)
  - `chunk_sort.c`: Alternative chunk sorting specifically for 200-350 elements
  - `radix_sort.c`: Bit-wise radix sort for >500 elements, processes each bit position
  - `turk_algorithm.c`: Turkish algorithm variant (available but not currently used)
  - `lis_sort.c`: Longest Increasing Subsequence approach (available but not currently used)
  - Multiple experimental algorithms in development (enhanced_radix, turbo_sort, etc.)

## Development Notes

- The project follows 42's norminette coding standards
- The `checker_linux` binary is used to validate that operations correctly sort the input
- Memory leaks are checked with valgrind as part of the testing process
- The libft library in `src/utils_libft/` provides standard C library replacements
- Error output: "Error\n" to stderr for invalid input (non-integers, duplicates, overflow)
- Empty input should produce no output

## Current Status (Last Updated: 2025/06/04)

### Algorithm Selection Strategy
Current algorithm selection in `src/sort/push_swap.c`:
- Size 2: `sort_two()` 
- Size 3: `sort_three()`
- Size 4: `sort_four()`
- Size 5: `sort_five()`
- Size ≤100: `optimized_sort()` - **100% success rate** (all tests <700 operations)
- Size ≤500: `dp_enhanced_sort()` - **Under development** (correctness issues)
- Size >500: `radix_sort()`

### Performance Results
- **100 elements**: 100% success rate with average ~664 operations using `optimized_sort()`
- **500 elements**: Previous best was 85% success rate (~5251 avg) with `improved_operation_driven_sort()`

### Recent Development: Dynamic Programming Enhanced Sort

#### User Request
User requested an "operation-driven design" approach (操作ドリブンで設計すること) focusing on analyzing each operation's characteristics and finding optimal combinations. When 100 elements achieved 100% success, user suggested keeping it fixed and focusing only on 500 elements.

#### Implementation Progress
1. **Operation Analysis**: Created comprehensive documentation in `/docs/operation_analysis.md`
2. **Operation-Driven Algorithms**: 
   - `operation_driven_sort.c`: Initial implementation (high variance)
   - `improved_operation_driven_sort.c`: 85% success rate for 500 elements
   - `precision_cost_sort.c`: Complex cost calculation (performed worse)
3. **Dynamic Programming Approach**: 
   - `dp_enhanced_sort.c`: Implements DP with memoization for small states
   - **Current Issue**: Algorithm produces correct operation counts (~4000) but fails checker validation
   - **Root Cause**: Suspected issue in move selection logic after chunking phase

#### Technical Insights Discovered
- Simple cost calculations outperform complex ones
- Chunk-based approaches are essential for stability  
- Operation-driven approach shows promise but needs refinement
- DP memoization effective for small state spaces (≤12 elements)

#### Current Investigation
The `dp_enhanced_sort` algorithm shows excellent operation counts (3900-4000 for 500 elements) but fails correctness validation. The issue appears to be in the `dp_guided_move_selection` or `execute_dp_guided_move` functions during the move-back phase.

#### Next Steps
Need to create a hybrid approach that combines:
- Working chunking phase from `dp_enhanced_sort`  
- Proven move-back logic from `improved_operation_driven_sort`
- This should achieve both good performance and 100% correctness

### Development Notes
- Multiple experimental algorithms available for comparison
- Debug helper functions in `src/debug_helper.c`
- Comprehensive test framework with checker validation
- All algorithms use `rank_normalize()` for value normalization before sorting