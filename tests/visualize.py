#!/usr/bin/env python3

import sys
import subprocess
import time
import os

def clear_screen():
    """Clear the terminal screen."""
    os.system('cls' if os.name == 'nt' else 'clear')

def parse_stacks(line):
    """Parse a stack state line into two stacks."""
    if "Stack a:" in line and "Stack b:" in line:
        parts = line.split("Stack b:")
        stack_a_part = parts[0].replace("Stack a:", "").strip()
        stack_b_part = parts[1].strip()
        
        stack_a = [int(x) for x in stack_a_part.split() if x]
        stack_b = [int(x) for x in stack_b_part.split() if x]
        
        return stack_a, stack_b
    return [], []

def visualize_stacks(stack_a, stack_b, step, operation=""):
    """Visualize the two stacks side by side."""
    clear_screen()
    
    max_height = max(len(stack_a), len(stack_b), 1)
    max_width_a = max([len(str(x)) for x in stack_a] + [1])
    max_width_b = max([len(str(x)) for x in stack_b] + [1])
    
    print(f"Step {step}: {operation}")
    print("┌" + "─" * (max_width_a + 2) + "┐ ┌" + "─" * (max_width_b + 2) + "┐")
    
    for i in range(max_height):
        a_val = str(stack_a[i]) if i < len(stack_a) else " "
        b_val = str(stack_b[i]) if i < len(stack_b) else " "
        
        a_padding = " " * (max_width_a - len(a_val))
        b_padding = " " * (max_width_b - len(b_val))
        
        print(f"│ {a_val}{a_padding} │ │ {b_val}{b_padding} │")
    
    print("└" + "─" * (max_width_a + 2) + "┘ └" + "─" * (max_width_b + 2) + "┘")
    print(f"  Stack A    Stack B  ")
    print()
    
    if operation:
        input("Press Enter to continue...")

def visualize_sorting(numbers):
    """Run push_swap with debug output and visualize the stacks."""
    cmd = ["./push_swap"]
    cmd.extend(numbers)
    
    env = os.environ.copy()
    env["DEBUG"] = "1"  # Enable debug output
    
    process = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, 
                              text=True, env=env)
    
    stack_a = [int(x) for x in numbers]
    stack_b = []
    
    operations = []
    step = 0
    
    visualize_stacks(stack_a, stack_b, step)
    time.sleep(0.5)
    
    for line in process.stderr:
        line = line.strip()
        if line.startswith("Operation:"):
            operation = line.replace("Operation:", "").strip()
            operations.append(operation)
            step += 1
        elif line.startswith("Stack a:"):
            stack_a, stack_b = parse_stacks(line)
            visualize_stacks(stack_a, stack_b, step, operations[-1] if operations else "")
            time.sleep(0.2)
    
    print(f"Sorting completed in {len(operations)} operations.")
    return operations

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python3 visualize.py <num1> <num2> ... <numN>")
        sys.exit(1)
    
    visualize_sorting(sys.argv[1:])