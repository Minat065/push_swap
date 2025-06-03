/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_n.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 19:29:26 by mirokugo          #+#    #+#             */
/*   Updated: 2025/06/03 20:00:00 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

void	sort_two(t_stack *a)
{
	// If top element is greater than element below it, swap them
	// Goal: smallest value at top, largest at bottom
	if (a->data[a->top] > a->data[a->top - 1])
		swap_a(a);
}

void	sort_three(t_stack *a)
{
	int	top;
	int	mid;
	int	bot;

	top = a->data[a->top];
	mid = a->data[a->top - 1];
	bot = a->data[a->top - 2];
	if (top > mid && mid < bot && top < bot)
		swap_a(a);
	else if (top > mid && mid > bot)
	{
		swap_a(a);
		reverse_rotate_a(a);
	}
	else if (top > mid && mid < bot && top > bot)
		rotate_a(a);
	else if (top < mid && mid > bot && top < bot)
	{
		swap_a(a);
		rotate_a(a);
	}
	else if (top < mid && mid > bot && top > bot)
		reverse_rotate_a(a);
}

static int	find_min_pos(t_stack *stack, int size)
{
	int	min_val;
	int	min_pos;
	int	i;

	min_val = stack->data[stack->top];
	min_pos = 0;
	i = 0;
	while (i < size)
	{
		if (stack->data[stack->top - i] < min_val)
		{
			min_val = stack->data[stack->top - i];
			min_pos = i;
		}
		i++;
	}
	return (min_pos);
}

void	sort_four(t_stack *a, t_stack *b)
{
	int	min_pos;

	min_pos = find_min_pos(a, 4);
	if (min_pos == 1)
		swap_a(a);
	else if (min_pos == 2)
	{
		rotate_a(a);
		rotate_a(a);
	}
	else if (min_pos == 3)
		reverse_rotate_a(a);
	push_atob(a, b);
	sort_three(a);
	push_btoa(b, a);
}

void	sort_five(t_stack *a, t_stack *b)
{
	int	min_pos;
	int	pushed;

	pushed = 0;
	while (pushed < 2)
	{
		min_pos = find_min_pos(a, 5 - pushed);
		if (min_pos == 0)
		{
			push_atob(a, b);
			pushed++;
		}
		else if (min_pos <= (5 - pushed) / 2)
			rotate_a(a);
		else
			reverse_rotate_a(a);
	}
	sort_three(a);
	push_btoa(b, a);
	push_btoa(b, a);
}
