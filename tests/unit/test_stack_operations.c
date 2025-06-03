/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_stack_operations.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 20:30:00 by mirokugo          #+#    #+#             */
/*   Updated: 2025/06/03 20:30:00 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/tests.h"

int test_stack_init(void)
{
	t_stack *stack;

	stack = create_test_stack(5);
	TEST_ASSERT(stack != NULL, "Stack creation should succeed");
	TEST_ASSERT(stack->data != NULL, "Stack data should be allocated");
	TEST_ASSERT(stack->top == -1, "New stack should be empty (top = -1)");
	TEST_ASSERT(stack->size == 5, "Stack size should be set correctly");
	
	free_test_stack(stack);
	return (1);
}

int test_push_pop_operations(void)
{
	t_stack *stack;
	int result;

	stack = create_test_stack(5);
	
	// Test push operation
	result = push(stack, 42);
	TEST_ASSERT(result == 1, "Push should return 1 on success");
	TEST_ASSERT(stack->top == 0, "Top should be 0 after first push");
	TEST_ASSERT(stack->data[0] == 42, "Pushed value should be stored correctly");
	
	// Test push multiple values
	push(stack, 24);
	push(stack, 12);
	TEST_ASSERT(stack->top == 2, "Top should be 2 after three pushes");
	TEST_ASSERT(stack->data[2] == 12, "Last pushed value should be at top");
	
	// Test pop operation
	result = pop(stack);
	TEST_ASSERT(result == 12, "Pop should return last pushed value");
	TEST_ASSERT(stack->top == 1, "Top should decrease after pop");
	
	result = pop(stack);
	TEST_ASSERT(result == 24, "Pop should return second value");
	
	result = pop(stack);
	TEST_ASSERT(result == 42, "Pop should return first value");
	TEST_ASSERT(stack->top == -1, "Stack should be empty after popping all");
	
	free_test_stack(stack);
	return (1);
}

int test_swap_operations(void)
{
	t_stack *stack_a;
	t_stack *stack_b;
	int values_a[] = {1, 2, 3};
	int values_b[] = {4, 5};

	stack_a = create_test_stack(5);
	stack_b = create_test_stack(5);
	
	setup_stack_with_values(stack_a, values_a, 3);
	setup_stack_with_values(stack_b, values_b, 2);
	
	// Test sa (swap a)
	swap_a_silent(stack_a);
	TEST_ASSERT(stack_a->data[stack_a->top] == 2, "sa: Top should be swapped");
	TEST_ASSERT(stack_a->data[stack_a->top - 1] == 3, "sa: Second should be swapped");
	TEST_ASSERT(stack_a->data[0] == 1, "sa: Bottom should remain unchanged");
	
	// Test sb (swap b)  
	swap_b_silent(stack_b);
	TEST_ASSERT(stack_b->data[stack_b->top] == 4, "sb: Top should be swapped");
	TEST_ASSERT(stack_b->data[stack_b->top - 1] == 5, "sb: Second should be swapped");
	
	// Test swap with single element (should do nothing)
	t_stack *single = create_test_stack(5);
	push(single, 100);
	swap_a_silent(single);
	TEST_ASSERT(single->data[0] == 100, "Swap with single element should do nothing");
	
	free_test_stack(stack_a);
	free_test_stack(stack_b);
	free_test_stack(single);
	return (1);
}

int test_push_operations(void)
{
	t_stack *stack_a;
	t_stack *stack_b;
	int values_a[] = {1, 2, 3};

	stack_a = create_test_stack(5);
	stack_b = create_test_stack(5);
	
	setup_stack_with_values(stack_a, values_a, 3);
	
	// Test pb (push from a to b)
	push_atob_silent(stack_a, stack_b);
	TEST_ASSERT(stack_a->top == 1, "pb: Source stack top should decrease");
	TEST_ASSERT(stack_b->top == 0, "pb: Destination stack top should increase");
	TEST_ASSERT(stack_b->data[0] == 3, "pb: Transferred value should be correct");
	TEST_ASSERT(stack_a->data[stack_a->top] == 2, "pb: Source top should be updated");
	
	// Test pa (push from b to a)  
	push_btoa_silent(stack_b, stack_a);
	TEST_ASSERT(stack_b->top == -1, "pa: Source stack should be empty");
	TEST_ASSERT(stack_a->top == 2, "pa: Destination stack top should increase");
	TEST_ASSERT(stack_a->data[stack_a->top] == 3, "pa: Transferred value should be on top");
	
	free_test_stack(stack_a);
	free_test_stack(stack_b);
	return (1);
}

int test_rotate_operations(void)
{
	t_stack *stack;
	int values[] = {1, 2, 3, 4};

	stack = create_test_stack(5);
	setup_stack_with_values(stack, values, 4);
	
	// Test ra (rotate a)
	rotate_a_silent(stack);
	TEST_ASSERT(stack->data[0] == 4, "ra: First element should move to bottom");
	TEST_ASSERT(stack->data[1] == 1, "ra: Second element should move up");
	TEST_ASSERT(stack->data[2] == 2, "ra: Third element should move up");
	TEST_ASSERT(stack->data[3] == 3, "ra: Top element should move up");
	TEST_ASSERT(stack->top == 3, "ra: Top index should remain same");
	
	free_test_stack(stack);
	return (1);
}

int test_reverse_rotate_operations(void)
{
	t_stack *stack;
	int values[] = {1, 2, 3, 4};

	stack = create_test_stack(5);
	setup_stack_with_values(stack, values, 4);
	
	// Test rra (reverse rotate a)
	reverse_rotate_a_silent(stack);
	TEST_ASSERT(stack->data[0] == 2, "rra: Second element should move to bottom");
	TEST_ASSERT(stack->data[1] == 3, "rra: Third element should stay");
	TEST_ASSERT(stack->data[2] == 4, "rra: Fourth element should stay");
	TEST_ASSERT(stack->data[3] == 1, "rra: Bottom element should move to top");
	TEST_ASSERT(stack->top == 3, "rra: Top index should remain same");
	
	free_test_stack(stack);
	return (1);
}