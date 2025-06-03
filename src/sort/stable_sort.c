/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stable_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minato <minato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:00:00 by minato            #+#    #+#             */
/*   Updated: 2025/01/06 13:00:00 by minato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

static void	smart_rotate_to_push(t_stack *a, int target_min, int target_max)
{
	int	size;
	int	best_pos;
	int	best_cost;
	int	i;
	int	cost;

	size = a->top + 1;
	best_pos = -1;
	best_cost = INT_MAX;
	i = 0;
	while (i < size)
	{
		if (a->data[a->top - i] >= target_min && 
			a->data[a->top - i] <= target_max)
		{
			if (i <= size / 2)
				cost = i;
			else
				cost = size - i;
			if (cost < best_cost)
			{
				best_cost = cost;
				best_pos = i;
			}
		}
		i++;
	}
	if (best_pos == -1)
		return;
	if (best_pos <= size / 2)
	{
		while (best_pos-- > 0)
			rotate_a(a);
	}
	else
	{
		best_pos = size - best_pos;
		while (best_pos-- > 0)
			reverse_rotate_a(a);
	}
}

static void	push_chunk_optimized(t_stack *a, t_stack *b, int min_val, int max_val)
{
	int	count;
	int	total;
	int	i;
	int	size;

	total = 0;
	size = a->top + 1;
	i = 0;
	while (i < size)
	{
		if (a->data[i] >= min_val && a->data[i] <= max_val)
			total++;
		i++;
	}
	count = 0;
	while (count < total)
	{
		smart_rotate_to_push(a, min_val, max_val);
		push_atob(a, b);
		if (b->top > 0 && b->data[b->top] < min_val + (max_val - min_val) / 3)
			rotate_b(b);
		count++;
	}
}

static void	optimized_push_back(t_stack *a, t_stack *b)
{
	int	max_val;
	int	max_pos;
	int	size;
	int	i;

	while (b->top >= 0)
	{
		size = b->top + 1;
		max_val = INT_MIN;
		max_pos = 0;
		i = 0;
		while (i < size)
		{
			if (b->data[i] > max_val)
			{
				max_val = b->data[i];
				max_pos = b->top - i;
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

void	stable_sort(t_stack *a, t_stack *b)
{
	int	size;
	int	chunk_size;
	int	chunks;
	int	i;

	size = a->top + 1;
	rank_normalize(a);
	
	if (size <= 20)
		chunk_size = 5;
	else if (size <= 100)
		chunk_size = 12;
	else if (size <= 200)
		chunk_size = 25;
	else if (size <= 500)
		chunk_size = 45;
	else
		chunk_size = 60;
	
	chunks = (size + chunk_size - 1) / chunk_size;
	i = 0;
	while (i < chunks)
	{
		int min_val = i * chunk_size;
		int max_val = (i + 1) * chunk_size - 1;
		if (max_val >= size)
			max_val = size - 1;
		push_chunk_optimized(a, b, min_val, max_val);
		i++;
	}
	optimized_push_back(a, b);
}