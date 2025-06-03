/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cost_based_radix_sort.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minato <minato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 11:00:00 by minato            #+#    #+#             */
/*   Updated: 2025/01/06 11:00:00 by minato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

typedef struct s_bit_cost
{
	int	index;
	int	value;
	int	bit_value;
	int	rotation_cost;
}	t_bit_cost;

static int	get_max_bits(int max_val)
{
	int	bits;

	bits = 0;
	while ((max_val >> bits) != 0)
		bits++;
	return (bits);
}

static int	calculate_rotation_cost(int position, int size)
{
	int	forward_cost;
	int	backward_cost;

	forward_cost = position;
	backward_cost = size - position;
	if (forward_cost <= backward_cost)
		return (forward_cost);
	return (backward_cost);
}

static t_bit_cost	find_cheapest_zero_bit(t_stack *stack, int bit)
{
	t_bit_cost	cheapest;
	t_bit_cost	current;
	int			size;
	int			i;

	size = stack->top + 1;
	cheapest.rotation_cost = INT_MAX;
	cheapest.index = -1;
	i = 0;
	while (i < size)
	{
		current.index = stack->top - i;
		current.value = stack->data[current.index];
		current.bit_value = (current.value >> bit) & 1;
		if (current.bit_value == 0)
		{
			current.rotation_cost = calculate_rotation_cost(i, size);
			if (current.rotation_cost < cheapest.rotation_cost)
				cheapest = current;
		}
		i++;
	}
	return (cheapest);
}

static void	execute_rotation_to_top(t_stack *stack, int position)
{
	int	size;
	int	forward_cost;
	int	backward_cost;

	size = stack->top + 1;
	forward_cost = position;
	backward_cost = size - position;
	
	if (forward_cost <= backward_cost)
	{
		while (forward_cost-- > 0)
			rotate_a(stack);
	}
	else
	{
		while (backward_cost-- > 0)
			reverse_rotate_a(stack);
	}
}

static void	process_bit_optimized(t_stack *a, t_stack *b, int bit, int size)
{
	int			processed;
	int			zeros_to_push;
	int			i;
	t_bit_cost	cheapest;

	zeros_to_push = 0;
	i = 0;
	while (i < size)
	{
		if (((a->data[i] >> bit) & 1) == 0)
			zeros_to_push++;
		i++;
	}
	processed = 0;
	while (processed < zeros_to_push)
	{
		cheapest = find_cheapest_zero_bit(a, bit);
		if (cheapest.index == -1)
			break;
		execute_rotation_to_top(a, a->top - cheapest.index);
		push_atob(a, b);
		processed++;
	}
	i = zeros_to_push;
	while (i < size)
	{
		if (((a->data[a->top] >> bit) & 1) == 1)
			rotate_a(a);
		else
			push_atob(a, b);
		i++;
	}
}

static void	smart_push_back(t_stack *a, t_stack *b)
{
	while (b->top >= 0)
		push_btoa(b, a);
}

void	cost_based_radix_sort(t_stack *stack_a, t_stack *stack_b)
{
	int	max_bits;
	int	size;
	int	i;

	size = stack_a->top + 1;
	rank_normalize(stack_a);
	max_bits = get_max_bits(size - 1);
	
	i = 0;
	while (i < max_bits)
	{
		process_bit_optimized(stack_a, stack_b, i, size);
		smart_push_back(stack_a, stack_b);
		i++;
	}
}