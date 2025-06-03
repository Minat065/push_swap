/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ultra_efficient_500.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minato <minato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:00:00 by minato            #+#    #+#             */
/*   Updated: 2025/01/06 16:00:00 by minato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

static void	ultra_push_chunks(t_stack *a, t_stack *b)
{
	int	size;
	int	chunk_size;
	int	chunk;
	int	i;

	size = a->top + 1;
	chunk_size = 35;
	chunk = 0;
	
	while (a->top > 2)
	{
		int min_chunk = chunk * chunk_size;
		int max_chunk = (chunk + 1) * chunk_size - 1;
		if (max_chunk >= size)
			max_chunk = size - 1;
		
		int moved = 0;
		int max_moves = max_chunk - min_chunk + 1;
		
		for (i = 0; i < size * 2 && moved < max_moves && a->top > 2; i++)
		{
			if (a->data[a->top] >= min_chunk && a->data[a->top] <= max_chunk)
			{
				push_atob(a, b);
				moved++;
				
				if (b->top > 0)
				{
					int mid = min_chunk + (max_chunk - min_chunk) / 2;
					if (b->data[b->top] < mid)
						rotate_b(b);
				}
			}
			else
				rotate_a(a);
		}
		chunk++;
	}
}

static void	ultra_push_back(t_stack *a, t_stack *b)
{
	while (b->top >= 0)
	{
		int max_val = INT_MIN;
		int max_pos = -1;
		int size_b = b->top + 1;
		int i;
		
		for (i = 0; i < size_b; i++)
		{
			if (b->data[i] > max_val)
			{
				max_val = b->data[i];
				max_pos = i;
			}
		}
		
		max_pos = b->top - max_pos;
		
		if (max_pos == 0)
		{
			push_btoa(b, a);
		}
		else if (max_pos <= size_b / 2)
		{
			while (max_pos-- > 0)
				rotate_b(b);
			push_btoa(b, a);
		}
		else
		{
			int rev_rotations = size_b - max_pos;
			while (rev_rotations-- > 0)
				reverse_rotate_b(b);
			push_btoa(b, a);
		}
	}
}

void	ultra_efficient_500(t_stack *a, t_stack *b)
{
	rank_normalize(a);
	ultra_push_chunks(a, b);
	sort_three(a);
	ultra_push_back(a, b);
}