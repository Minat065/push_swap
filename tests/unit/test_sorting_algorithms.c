/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_sorting_algorithms.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 20:30:00 by mirokugo          #+#    #+#             */
/*   Updated: 2025/06/03 20:30:00 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/tests.h"

int test_is_sorted_function(void)
{
	t_stack *stack;
	int sorted_values[] = {5, 4, 3, 2, 1};  // Push order: 5 bottom, 1 top (sorted!)
	int unsorted_values[] = {3, 1, 4, 2, 5};  // Random order
	int single_value[] = {42};

	stack = create_test_stack(10);
	
	// Test sorted array: smallest (1) at top, largest (5) at bottom
	setup_stack_with_values(stack, sorted_values, 5);
	TEST_ASSERT(is_sorted(stack) == 1, "Sorted array should return 1");
	
	// Test unsorted array
	setup_stack_with_values(stack, unsorted_values, 5);
	TEST_ASSERT(is_sorted(stack) == 0, "Unsorted array should return 0");
	
	// Test single element
	setup_stack_with_values(stack, single_value, 1);
	TEST_ASSERT(is_sorted(stack) == 1, "Single element should be considered sorted");
	
	// Test empty stack
	stack->top = -1;
	TEST_ASSERT(is_sorted(stack) == 1, "Empty stack should be considered sorted");
	
	free_test_stack(stack);
	return (1);
}

int test_sort_two_elements(void)
{
	t_stack *stack;
	int values[] = {2, 1};  // Push order: 2 bottom, 1 top - needs swap

	stack = create_test_stack(5);
	setup_stack_with_values(stack, values, 2);
	
	sort_two(stack);
	TEST_ASSERT(is_sorted(stack) == 1, "Two elements should be sorted");
	TEST_ASSERT(stack->data[0] == 2, "Bottom element should be 2");
	TEST_ASSERT(stack->data[1] == 1, "Top element should be 1 (smallest)");
	
	free_test_stack(stack);
	return (1);
}

int test_sort_three_elements(void)
{
	t_stack *stack;
	int test_cases[][3] = {
		{3, 2, 1},
		{1, 3, 2},
		{2, 1, 3},
		{2, 3, 1},
		{3, 1, 2},
		{1, 2, 3}  // already sorted
	};
	int i;

	i = 0;
	while (i < 6)
	{
		stack = create_test_stack(5);
		setup_stack_with_values(stack, test_cases[i], 3);
		
		sort_three(stack);
		TEST_ASSERT(is_sorted(stack) == 1, "Three elements should be sorted");
		
		free_test_stack(stack);
		i++;
	}
	return (1);
}

int test_sort_small_arrays(void)
{
	t_stack *stack_a;
	t_stack *stack_b;
	int values_4[] = {4, 2, 1, 3};
	int values_5[] = {5, 3, 1, 4, 2};

	// Test 4 elements
	stack_a = create_test_stack(10);
	stack_b = create_test_stack(10);
	setup_stack_with_values(stack_a, values_4, 4);
	
	sort_four(stack_a, stack_b);
	TEST_ASSERT(is_sorted(stack_a) == 1, "Four elements should be sorted");
	TEST_ASSERT(stack_b->top == -1, "Stack B should be empty after sorting");
	
	free_test_stack(stack_a);
	free_test_stack(stack_b);
	
	// Test 5 elements
	stack_a = create_test_stack(10);
	stack_b = create_test_stack(10);
	setup_stack_with_values(stack_a, values_5, 5);
	
	sort_five(stack_a, stack_b);
	TEST_ASSERT(is_sorted(stack_a) == 1, "Five elements should be sorted");
	TEST_ASSERT(stack_b->top == -1, "Stack B should be empty after sorting");
	
	free_test_stack(stack_a);
	free_test_stack(stack_b);
	return (1);
}