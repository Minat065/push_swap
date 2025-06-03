/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_operations_silent.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 20:45:00 by mirokugo          #+#    #+#             */
/*   Updated: 2025/06/03 20:45:00 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tests.h"

// Silent versions of operations for testing (no printf output)

void swap_a_silent(t_stack *stack_a)
{
	int tmp;

	if (stack_a->top < 1)
		return ;
	tmp = stack_a->data[stack_a->top];
	stack_a->data[stack_a->top] = stack_a->data[stack_a->top - 1];
	stack_a->data[stack_a->top - 1] = tmp;
}

void swap_b_silent(t_stack *stack_b)
{
	int tmp;

	if (stack_b->top < 1)
		return ;
	tmp = stack_b->data[stack_b->top];
	stack_b->data[stack_b->top] = stack_b->data[stack_b->top - 1];
	stack_b->data[stack_b->top - 1] = tmp;
}

int push_atob_silent(t_stack *src, t_stack *dst)
{
	if (src->top == -1)
		return (1);
	push(dst, src->data[src->top]);
	src->top--;
	return (0);
}

int push_btoa_silent(t_stack *src, t_stack *dst)
{
	if (src->top == -1)
		return (1);
	push(dst, src->data[src->top]);
	src->top--;
	return (0);
}

void rotate_a_silent(t_stack *stack_a)
{
	int i;
	int tmp;

	if (stack_a->top < 1)
		return ;
	i = stack_a->top;
	tmp = stack_a->data[stack_a->top];
	while (i > 0)
	{
		stack_a->data[i] = stack_a->data[i - 1];
		i--;
	}
	stack_a->data[0] = tmp;
}

void rotate_b_silent(t_stack *stack_b)
{
	int i;
	int tmp;

	if (stack_b->top < 1)
		return ;
	i = stack_b->top;
	tmp = stack_b->data[stack_b->top];
	while (i > 0)
	{
		stack_b->data[i] = stack_b->data[i - 1];
		i--;
	}
	stack_b->data[0] = tmp;
}

void reverse_rotate_a_silent(t_stack *stack_a)
{
	int i;
	int tmp;

	if (stack_a->top < 1)
		return ;
	i = 0;
	tmp = stack_a->data[0];
	while (i < stack_a->top)
	{
		stack_a->data[i] = stack_a->data[i + 1];
		i++;
	}
	stack_a->data[stack_a->top] = tmp;
}

void reverse_rotate_b_silent(t_stack *stack_b)
{
	int i;
	int tmp;

	if (stack_b->top < 1)
		return ;
	i = 0;
	tmp = stack_b->data[0];
	while (i < stack_b->top)
	{
		stack_b->data[i] = stack_b->data[i + 1];
		i++;
	}
	stack_b->data[stack_b->top] = tmp;
}