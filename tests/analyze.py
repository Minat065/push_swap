#!/usr/bin/env python3

import sys
import subprocess
import csv
import datetime
import os
from collections import Counter

def run_push_swap(numbers):
    """Run push_swap and return the operations."""
    cmd = ["./push_swap"]
    cmd.extend(numbers)
    
    process = subprocess.run(cmd, capture_output=True, text=True)
    operations = process.stdout.strip().split('\n')
    
    # Remove empty operations (if any)
    operations = [op for op in operations if op]
    
    return operations

def analyze_operations(operations):
    """Analyze the operations and return statistics."""
    op_count = len(operations)
    op_types = Counter(operations)
    
    # Group operations by category
    swap_ops = op_types.get('sa', 0) + op_types.get('sb', 0) + op_types.get('ss', 0)
    push_ops = op_types.get('pa', 0) + op_types.get('pb', 0)
    rotate_ops = op_types.get('ra', 0) + op_types.get('rb', 0) + op_types.get('rr', 0)
    rev_rotate_ops = op_types.get('rra', 0) + op_types.get('rrb', 0) + op_types.get('rrr', 0)
    
    # Check for potential optimizations
    potential_rr = min(op_types.get('ra', 0), op_types.get('rb', 0))
    potential_rrr = min(op_types.get('rra', 0), op_types.get('rrb', 0))
    potential_ss = min(op_types.get('sa', 0), op_types.get('sb', 0))
    
    optimized_count = op_count - potential_rr - potential_rrr - potential_ss
    
    return {
        'total': op_count,
        'swap': swap_ops,
        'push': push_ops,
        'rotate': rotate_ops,
        'rev_rotate': rev_rotate_ops,
        'types': dict(op_types),
        'potential_optimized': optimized_count
    }

def save_to_csv(size, stats, filename='push_swap_stats.csv'):
    """Save the statistics to a CSV file."""
    file_exists = os.path.isfile(filename)
    
    with open(filename, 'a', newline='') as csvfile:
        fieldnames = ['date', 'size', 'total_ops', 'swap_ops', 'push_ops', 
                     'rotate_ops', 'rev_rotate_ops', 'sa', 'sb', 'ss', 
                     'pa', 'pb', 'ra', 'rb', 'rr', 'rra', 'rrb', 'rrr',
                     'potential_optimized']
        
        writer = csv.DictWriter(csvfile, fieldnames=fieldnames)
        
        if not file_exists:
            writer.writeheader()
        
        row = {
            'date': datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S'),
            'size': size,
            'total_ops': stats['total'],
            'swap_ops': stats['swap'],
            'push_ops': stats['push'],
            'rotate_ops': stats['rotate'],
            'rev_rotate_ops': stats['rev_rotate'],
            'potential_optimized': stats['potential_optimized']
        }
        
        # Add individual operation counts
        for op, count in stats['types'].items():
            row[op] = count
        
        writer.writerow(row)

def print_stats(stats):
    """Print the statistics in a readable format."""
    print("\n==== PUSH_SWAP OPERATION STATISTICS ====")
    print(f"Total operations: {stats['total']}")
    print("\nOperation breakdown:")
    print(f"  Swap operations: {stats['swap']} ({stats['swap']/stats['total']*100:.1f}%)")
    print(f"  Push operations: {stats['push']} ({stats['push']/stats['total']*100:.1f}%)")
    print(f"  Rotate operations: {stats['rotate']} ({stats['rotate']/stats['total']*100:.1f}%)")
    print(f"  Rev-rotate operations: {stats['rev_rotate']} ({stats['rev_rotate']/stats['total']*100:.1f}%)")
    
    print("\nDetailed operation counts:")
    for op, count in sorted(stats['types'].items()):
        print(f"  {op}: {count}")
    
    print("\nOptimization potential:")
    print(f"  Potentially optimized count: {stats['potential_optimized']}")
    potential_savings = stats['total'] - stats['potential_optimized']
    if potential_savings > 0:
        print(f"  Potential savings: {potential_savings} operations ({potential_savings/stats['total']*100:.1f}%)")
    else:
        print("  Already fully optimized!")

def main():
    if len(sys.argv) < 2:
        print("Usage: python3 analyze.py <num1> <num2> ... <numN>")
        print("   or: python3 analyze.py --random <size>")
        sys.exit(1)
    
    if sys.argv[1] == "--random":
        if len(sys.argv) != 3:
            print("Usage for random numbers: python3 analyze.py --random <size>")
            sys.exit(1)
        
        size = int(sys.argv[2])
        # Generate random numbers
        cmd = ["python3", "generate_random.py", str(size)]
        process = subprocess.run(cmd, capture_output=True, text=True)
        numbers = process.stdout.strip().split()
    else:
        numbers = sys.argv[1:]
        size = len(numbers)
    
    print(f"Analyzing push_swap with {size} numbers...")
    operations = run_push_swap(numbers)
    
    if not operations:
        print("No operations returned. Make sure push_swap is working correctly.")
        sys.exit(1)
    
    stats = analyze_operations(operations)
    print_stats(stats)
    
    save_to_csv(size, stats)
    print(f"\nStatistics saved to push_swap_stats.csv")

if __name__ == "__main__":
    main()