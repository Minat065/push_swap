/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 20:00:00 by mirokugo          #+#    #+#             */
/*   Updated: 2025/06/03 20:00:00 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"
#include <math.h>

static int	calculate_chunk_size(int total_size)
{
	if (total_size <= 50)
		return (12);
	else if (total_size <= 100)
		return (17);
	else if (total_size <= 500)
		return (42);
	else
		return (35);
}

static int	find_closest_in_chunk(t_stack *a, int chunk_min, int chunk_max)
{
	int	i;
	int	size;
	int	min_rotations;
	int	best_pos;

	size = a->top + 1;
	min_rotations = size;
	best_pos = -1;
	i = 0;
	while (i < size)
	{
		if (a->data[a->top - i] >= chunk_min && a->data[a->top - i] <= chunk_max)
		{
			int	rotations = (i <= size / 2) ? i : size - i;
			if (rotations < min_rotations)
			{
				min_rotations = rotations;
				best_pos = i;
			}
		}
		i++;
	}
	return (best_pos);
}

static void	push_chunk_to_b(t_stack *a, t_stack *b, int chunk_min, int chunk_max)
{
	int	target_pos;
	int	size;

	while (a->top >= 0)
	{
		target_pos = find_closest_in_chunk(a, chunk_min, chunk_max);
		if (target_pos == -1)
			break;
		size = a->top + 1;
		if (target_pos <= size / 2)
		{
			while (target_pos-- > 0)
				rotate_a(a);
		}
		else
		{
			target_pos = size - target_pos;
			while (target_pos-- > 0)
				reverse_rotate_a(a);
		}
		push_atob(a, b);
		if (b->top > 0 && b->data[b->top] < chunk_min + (chunk_max - chunk_min) / 3)
			rotate_b(b);
	}
}

static void	push_back_to_a(t_stack *a, t_stack *b)
{
	int	max_val;
	int	max_pos;
	int	i;
	int	size;

	while (b->top >= 0)
	{
		max_val = b->data[b->top];
		max_pos = 0;
		size = b->top + 1;
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
			int rotations = size - max_pos;
			while (rotations-- > 0)
				reverse_rotate_b(b);
		}
		push_btoa(b, a);
	}
}

void	chunk_sort(t_stack *a, t_stack *b)
{
	int	total_size;
	int	chunk_size;
	int	chunk_count;
	int	i;

	total_size = a->top + 1;
	rank_normalize(a);
	chunk_size = calculate_chunk_size(total_size);
	chunk_count = (total_size + chunk_size - 1) / chunk_size;
	i = 0;
	while (i < chunk_count)
	{
		push_chunk_to_b(a, b, i * chunk_size, (i + 1) * chunk_size - 1);
		i++;
	}
	push_back_to_a(a, b);
}