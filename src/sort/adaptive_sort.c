/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adaptive_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minato <minato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 12:00:00 by minato            #+#    #+#             */
/*   Updated: 2025/01/06 12:00:00 by minato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

static int	count_inversions(t_stack *stack)
{
	int	inversions;
	int	i;
	int	j;
	int	size;

	inversions = 0;
	size = stack->top + 1;
	i = 0;
	while (i < size - 1)
	{
		j = i + 1;
		while (j < size)
		{
			if (stack->data[i] > stack->data[j])
				inversions++;
			j++;
		}
		i++;
	}
	return (inversions);
}

static int	find_longest_sorted_sequence(t_stack *stack)
{
	int	max_length;
	int	current_length;
	int	i;
	int	size;

	size = stack->top + 1;
	if (size <= 1)
		return (size);
	max_length = 1;
	current_length = 1;
	i = 1;
	while (i < size)
	{
		if (stack->data[i - 1] < stack->data[i])
			current_length++;
		else
		{
			if (current_length > max_length)
				max_length = current_length;
			current_length = 1;
		}
		i++;
	}
	if (current_length > max_length)
		max_length = current_length;
	return (max_length);
}

static double	calculate_disorder_ratio(t_stack *stack)
{
	int		size;
	int		inversions;
	int		max_inversions;
	double	ratio;

	size = stack->top + 1;
	if (size <= 1)
		return (0.0);
	inversions = count_inversions(stack);
	max_inversions = (size * (size - 1)) / 2;
	ratio = (double)inversions / (double)max_inversions;
	return (ratio);
}

static void	chunk_based_adaptive_sort(t_stack *a, t_stack *b)
{
	int	size;
	int	chunk_size;
	int	chunks;
	int	i;
	int	j;
	int	pushed;

	size = a->top + 1;
	rank_normalize(a);
	if (size <= 100)
		chunk_size = 20;
	else if (size <= 300)
		chunk_size = 35;
	else
		chunk_size = 45;
	chunks = (size + chunk_size - 1) / chunk_size;
	i = 0;
	while (i < chunks)
	{
		pushed = 0;
		j = 0;
		while (j < size && pushed < chunk_size)
		{
			if (a->data[a->top] >= i * chunk_size && 
				a->data[a->top] < (i + 1) * chunk_size)
			{
				push_atob(a, b);
				if (b->top > 0 && b->data[b->top] < b->data[b->top - 1])
					swap_b(b);
				pushed++;
			}
			else
				rotate_a(a);
			j++;
		}
		i++;
	}
	while (b->top >= 0)
	{
		int max_pos = 0;
		int max_val = b->data[0];
		j = 1;
		while (j <= b->top)
		{
			if (b->data[j] > max_val)
			{
				max_val = b->data[j];
				max_pos = j;
			}
			j++;
		}
		while (max_pos != b->top)
		{
			if (max_pos <= b->top / 2)
				reverse_rotate_b(b);
			else
				rotate_b(b);
			max_pos = (max_pos == 0) ? b->top : max_pos - 1;
		}
		push_btoa(b, a);
	}
}

void	adaptive_sort(t_stack *a, t_stack *b)
{
	int		size;
	double	disorder_ratio;
	int		sorted_length;

	size = a->top + 1;
	disorder_ratio = calculate_disorder_ratio(a);
	sorted_length = find_longest_sorted_sequence(a);
	
	if (disorder_ratio < 0.3 || sorted_length > size * 0.7)
	{
		operation_driven_sort(a, b);
	}
	else if (size <= 150)
	{
		operation_driven_sort(a, b);
	}
	else
	{
		chunk_based_adaptive_sort(a, b);
	}
}