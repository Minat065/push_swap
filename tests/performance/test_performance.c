/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_performance.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 21:30:00 by mirokugo          #+#    #+#             */
/*   Updated: 2025/06/03 21:30:00 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/tests.h"
#include <time.h>
#include <stdlib.h>

// Global operation counter
static int operation_count = 0;

// Silent versions of operations that count
void count_sa(t_stack *stack_a)
{
	swap_a_silent(stack_a);
	operation_count++;
}

void count_sb(t_stack *stack_b)
{
	swap_b_silent(stack_b);
	operation_count++;
}

void count_pa(t_stack *src, t_stack *dst)
{
	push_btoa_silent(src, dst);
	operation_count++;
}

void count_pb(t_stack *src, t_stack *dst)
{
	push_atob_silent(src, dst);
	operation_count++;
}

void count_ra(t_stack *stack_a)
{
	rotate_a_silent(stack_a);
	operation_count++;
}

void count_rb(t_stack *stack_b)
{
	rotate_b_silent(stack_b);
	operation_count++;
}

void count_rra(t_stack *stack_a)
{
	reverse_rotate_a_silent(stack_a);
	operation_count++;
}

void count_rrb(t_stack *stack_b)
{
	reverse_rotate_b_silent(stack_b);
	operation_count++;
}

// Test helper to generate random array
void generate_random_array(int *arr, int size)
{
	int i, j, temp;
	
	// Initialize array with values 1..size
	for (i = 0; i < size; i++)
		arr[i] = i + 1;
	
	// Fisher-Yates shuffle
	srand(time(NULL));
	for (i = size - 1; i > 0; i--)
	{
		j = rand() % (i + 1);
		temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;
	}
}

int test_100_elements_performance(void)
{
	t_stack *stack_a;
	t_stack *stack_b;
	int values[100];
	
	stack_a = create_test_stack(100);
	stack_b = create_test_stack(100);
	
	generate_random_array(values, 100);
	setup_stack_with_values(stack_a, values, 100);
	
	operation_count = 0;
	optimized_sort(stack_a, stack_b);
	
	TEST_ASSERT(is_sorted(stack_a) == 1, "100 elements should be sorted");
	TEST_ASSERT(operation_count < 700, "100 elements should use < 700 operations");
	printf("  100 elements used %d operations (target: < 700)\n", operation_count);
	
	free_test_stack(stack_a);
	free_test_stack(stack_b);
	return (1);
}

int test_500_elements_performance(void)
{
	t_stack *stack_a;
	t_stack *stack_b;
	int values[500];
	
	stack_a = create_test_stack(500);
	stack_b = create_test_stack(500);
	
	generate_random_array(values, 500);
	setup_stack_with_values(stack_a, values, 500);
	
	operation_count = 0;
	optimized_sort(stack_a, stack_b);
	
	TEST_ASSERT(is_sorted(stack_a) == 1, "500 elements should be sorted");
	TEST_ASSERT(operation_count < 5500, "500 elements should use < 5500 operations");
	printf("  500 elements used %d operations (target: < 5500)\n", operation_count);
	
	free_test_stack(stack_a);
	free_test_stack(stack_b);
	return (1);
}

int test_performance_multiple_runs(void)
{
	int runs = 10;
	int total_100 = 0, total_500 = 0;
	int max_100 = 0, max_500 = 0;
	int i;
	
	printf("  Running %d performance tests...\n", runs);
	
	for (i = 0; i < runs; i++)
	{
		t_stack *stack_a = create_test_stack(500);
		t_stack *stack_b = create_test_stack(500);
		int values[500];
		
		// Test 100 elements
		generate_random_array(values, 100);
		setup_stack_with_values(stack_a, values, 100);
		operation_count = 0;
		optimized_sort(stack_a, stack_b);
		total_100 += operation_count;
		if (operation_count > max_100) max_100 = operation_count;
		
		// Reset stacks for 500 test
		stack_a->top = -1;
		stack_b->top = -1;
		
		// Test 500 elements
		generate_random_array(values, 500);
		setup_stack_with_values(stack_a, values, 500);
		operation_count = 0;
		optimized_sort(stack_a, stack_b);
		total_500 += operation_count;
		if (operation_count > max_500) max_500 = operation_count;
		
		free_test_stack(stack_a);
		free_test_stack(stack_b);
	}
	
	printf("  100 elements - avg: %d, max: %d (target: < 700)\n", 
		total_100 / runs, max_100);
	printf("  500 elements - avg: %d, max: %d (target: < 5500)\n", 
		total_500 / runs, max_500);
	
	TEST_ASSERT(max_100 < 700, "100 elements max should be < 700");
	TEST_ASSERT(max_500 < 5500, "500 elements max should be < 5500");
	
	return (1);
}