/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimized_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 20:00:00 by mirokugo          #+#    #+#             */
/*   Updated: 2025/06/03 20:00:00 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

static void	smart_push_to_b(t_stack *a, t_stack *b, int min_val, int max_val)
{
	int	initial_size;
	int	processed;

	initial_size = a->top + 1;
	processed = 0;
	while (processed < initial_size)
	{
		if (a->data[a->top] >= min_val && a->data[a->top] <= max_val)
		{
			push_atob(a, b);
			if (b->top > 0 && b->data[b->top] < min_val + (max_val - min_val) / 2)
				rotate_b(b);
		}
		else
			rotate_a(a);
		processed++;
	}
}

static void	smart_push_back(t_stack *a, t_stack *b)
{
	int	max_val;
	int	max_pos;
	int	size;
	int	i;

	while (b->top >= 0)
	{
		size = b->top + 1;
		max_val = b->data[b->top];
		max_pos = 0;
		i = 0;
		while (i < size)
		{
			if (b->data[b->top - i] > max_val)
			{
				max_val = b->data[b->top - i];
				max_pos = i;
			}
			i++;
		}
		if (max_pos <= size / 2)
		{
			while (max_pos-- > 0)
				rotate_b(b);
		}
		else
		{
			max_pos = size - max_pos;
			while (max_pos-- > 0)
				reverse_rotate_b(b);
		}
		push_btoa(b, a);
	}
}

void	optimized_sort(t_stack *a, t_stack *b)
{
	int	size;
	int	chunk_size;
	int	i;

	size = a->top + 1;
	rank_normalize(a);
	
	if (size <= 100)
		chunk_size = 18;
	else if (size <= 200)
		chunk_size = 25;
	else if (size <= 500)
		chunk_size = 45;
	else
		chunk_size = 50;
	
	i = 0;
	while (i * chunk_size < size)
	{
		int min_val = i * chunk_size;
		int max_val = (i + 1) * chunk_size - 1;
		if (max_val >= size)
			max_val = size - 1;
		smart_push_to_b(a, b, min_val, max_val);
		i++;
	}
	smart_push_back(a, b);
}