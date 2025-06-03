/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turbo_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 21:30:00 by mirokugo          #+#    #+#             */
/*   Updated: 2025/06/03 21:30:00 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

static int	calculate_optimal_chunk_size(int size)
{
	if (size <= 3)
		return size;
	if (size <= 5)
		return 3;
	if (size <= 100)
		return 11;
	if (size <= 500)
		return 11;
	return 13;
}

static void	efficient_push_to_b(t_stack *a, t_stack *b, int min_val, int max_val)
{
	int	rotations;
	int	size;
	int	target_found;

	size = a->top + 1;
	rotations = 0;
	
	while (rotations < size)
	{
		target_found = 0;
		if (a->data[a->top] >= min_val && a->data[a->top] <= max_val)
		{
			push_atob(a, b);
			target_found = 1;
			
			// Smart rotation for stack B
			if (b->top > 0)
			{
				int b_size = b->top + 1;
				int mid_val = min_val + (max_val - min_val) / 2;
				
				// Only rotate if it helps with sorting
				if (b->data[b->top] < mid_val && b_size > 1)
					rotate_b(b);
			}
		}
		
		if (!target_found)
		{
			rotate_a(a);
			rotations++;
		}
		else
		{
			rotations = 0; // Reset counter when we find a target
		}
		
		// Break if we've checked all elements
		if (rotations >= size)
			break;
	}
}


static void	optimized_push_back(t_stack *a, t_stack *b)
{
	int	max_val;
	int	max_pos;
	int	size;
	int	cost_forward;
	int	cost_backward;
	int	i;

	while (b->top >= 0)
	{
		size = b->top + 1;
		max_val = b->data[b->top];
		max_pos = 0;
		
		// Find maximum value position
		for (i = 0; i < size; i++)
		{
			if (b->data[b->top - i] > max_val)
			{
				max_val = b->data[b->top - i];
				max_pos = i;
			}
		}
		
		// Calculate rotation costs
		cost_forward = max_pos;
		cost_backward = size - max_pos;
		
		// Choose optimal rotation direction
		if (cost_forward <= cost_backward)
		{
			while (max_pos-- > 0)
				rotate_b(b);
		}
		else
		{
			while (cost_backward-- > 0)
				reverse_rotate_b(b);
		}
		
		push_btoa(b, a);
	}
}

void	turbo_sort(t_stack *a, t_stack *b)
{
	int	size;
	int	chunk_size;
	int	num_chunks;
	int	i;

	size = a->top + 1;
	
	// Handle special cases
	if (size <= 1)
		return;
	if (size == 2)
	{
		if (a->data[a->top] > a->data[a->top - 1])
			swap_a(a);
		return;
	}
	if (size == 3)
	{
		sort_three(a);
		return;
	}
	if (size == 4)
	{
		sort_four(a, b);
		return;
	}
	if (size == 5)
	{
		sort_five(a, b);
		return;
	}
	
	// Normalize ranks for better performance
	rank_normalize(a);
	
	// Calculate optimal chunk size
	chunk_size = calculate_optimal_chunk_size(size);
	num_chunks = (size + chunk_size - 1) / chunk_size;
	
	// Push chunks to stack B in optimized order
	for (i = 0; i < num_chunks; i++)
	{
		int min_val = i * chunk_size;
		int max_val = (i + 1) * chunk_size - 1;
		
		if (max_val >= size)
			max_val = size - 1;
			
		efficient_push_to_b(a, b, min_val, max_val);
	}
	
	// Push everything back to A in sorted order
	optimized_push_back(a, b);
}