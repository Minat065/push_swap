/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_framework.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 20:30:00 by mirokugo          #+#    #+#             */
/*   Updated: 2025/06/03 20:30:00 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tests.h"
#include <stdlib.h>

// Global test counters
int tests_passed = 0;
int tests_failed = 0;
int total_tests = 0;

t_stack *create_test_stack(int size)
{
	t_stack *stack;

	stack = malloc(sizeof(t_stack));
	if (!stack)
		return (NULL);
	stack->data = malloc(sizeof(int) * size);
	if (!stack->data)
	{
		free(stack);
		return (NULL);
	}
	stack->top = -1;
	stack->size = size;
	return (stack);
}

void free_test_stack(t_stack *stack)
{
	if (stack)
	{
		if (stack->data)
			free(stack->data);
		free(stack);
	}
}

void setup_stack_with_values(t_stack *stack, int *values, int count)
{
	int i;

	stack->top = -1;
	i = 0;
	while (i < count)
	{
		stack->data[++stack->top] = values[i];
		i++;
	}
}

int arrays_equal(int *arr1, int *arr2, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		if (arr1[i] != arr2[i])
			return (0);
		i++;
	}
	return (1);
}

void print_test_summary(void)
{
	printf("\n=== TEST SUMMARY ===\n");
	printf("Total tests: %d\n", total_tests);
	printf("Passed: %d\n", tests_passed);
	printf("Failed: %d\n", tests_failed);
	printf("Success rate: %.1f%%\n", 
		total_tests > 0 ? (float)tests_passed / total_tests * 100 : 0);
	printf("===================\n");
}