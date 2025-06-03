/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_stack_structure.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 21:00:00 by mirokugo          #+#    #+#             */
/*   Updated: 2025/06/03 21:00:00 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tests.h"

int main(void)
{
	t_stack *stack;
	int values[] = {1, 2, 3, 4, 5};
	int i;

	printf("🔍 DEBUG: Understanding Stack Structure\n");
	printf("=========================================\n\n");

	stack = create_test_stack(10);
	setup_stack_with_values(stack, values, 5);

	printf("Stack after setup with values [1, 2, 3, 4, 5]:\n");
	printf("stack->top = %d\n", stack->top);
	
	i = 0;
	while (i <= stack->top)
	{
		printf("stack->data[%d] = %d\n", i, stack->data[i]);
		i++;
	}

	printf("\nTraversing from top to bottom:\n");
	i = stack->top;
	while (i >= 0)
	{
		printf("stack->data[%d] = %d (position from top: %d)\n", 
			i, stack->data[i], stack->top - i);
		i--;
	}

	printf("\nTesting is_sorted function:\n");
	printf("is_sorted result: %d\n", is_sorted(stack));

	printf("\nTesting sort_two with [2, 1]:\n");
	int values2[] = {2, 1};
	setup_stack_with_values(stack, values2, 2);
	printf("Before sort_two:\n");
	printf("  stack->data[0] = %d\n", stack->data[0]);
	printf("  stack->data[1] = %d (top)\n", stack->data[1]);
	printf("  is_sorted: %d\n", is_sorted(stack));
	printf("  Need swap? %s\n", stack->data[stack->top] > stack->data[stack->top - 1] ? "YES" : "NO");
	
	sort_two(stack);
	printf("After sort_two:\n");
	printf("  stack->data[0] = %d\n", stack->data[0]);
	printf("  stack->data[1] = %d (top)\n", stack->data[1]);
	printf("  is_sorted: %d\n", is_sorted(stack));

	free_test_stack(stack);
	return (0);
}