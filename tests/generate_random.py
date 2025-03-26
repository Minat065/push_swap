#!/usr/bin/env python3

import random
import sys

def generate_random_numbers(size, min_val=-1000, max_val=1000):
    """Generate a list of unique random integers."""
    numbers = set()
    while len(numbers) < size:
        numbers.add(random.randint(min_val, max_val))
    return list(numbers)

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python3 generate_random.py <size> [min_val] [max_val]")
        sys.exit(1)
    
    size = int(sys.argv[1])
    min_val = int(sys.argv[2]) if len(sys.argv) > 2 else -1000
    max_val = int(sys.argv[3]) if len(sys.argv) > 3 else 1000
    
    numbers = generate_random_numbers(size, min_val, max_val)
    print(" ".join(map(str, numbers)))