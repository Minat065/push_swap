/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guaranteed_sort.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minato <minato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:00:00 by minato            #+#    #+#             */
/*   Updated: 2025/01/06 15:00:00 by minato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

static int	get_max_bits(int max_val)
{
	int	bits;

	bits = 0;
	while ((max_val >> bits) != 0)
		bits++;
	return (bits);
}

static void	optimized_radix_100(t_stack *a, t_stack *b)
{
	int	max_bits;
	int	size;
	int	i;
	int	j;
	int	pushed;

	size = a->top + 1;
	max_bits = get_max_bits(size - 1);
	
	i = 0;
	while (i < max_bits)
	{
		pushed = 0;
		j = 0;
		while (j < size)
		{
			if (((a->data[a->top] >> i) & 1) == 0)
			{
				push_atob(a, b);
				pushed++;
			}
			else
				rotate_a(a);
			j++;
		}
		while (pushed-- > 0)
			push_btoa(b, a);
		i++;
	}
}

static void	fixed_chunk_sort(t_stack *a, t_stack *b)
{
	int	size;
	int	chunk_size;
	int	chunk_count;
	int	current_chunk;
	int	i;

	size = a->top + 1;
	chunk_size = 11;
	chunk_count = (size + chunk_size - 1) / chunk_size;
	
	current_chunk = 0;
	while (current_chunk < chunk_count)
	{
		int min_val = current_chunk * chunk_size;
		int max_val = (current_chunk + 1) * chunk_size - 1;
		if (max_val >= size)
			max_val = size - 1;
		
		int elements_in_chunk = max_val - min_val + 1;
		int pushed = 0;
		
		for (i = 0; i < size && pushed < elements_in_chunk; i++)
		{
			if (a->data[a->top] >= min_val && a->data[a->top] <= max_val)
			{
				push_atob(a, b);
				if (b->top > 0 && b->data[b->top] < b->data[b->top - 1])
					swap_b(b);
				pushed++;
			}
			else
				rotate_a(a);
		}
		current_chunk++;
	}
	
	while (b->top >= 0)
	{
		int max_pos = 0;
		int max_val = b->data[0];
		for (i = 1; i <= b->top; i++)
		{
			if (b->data[i] > max_val)
			{
				max_val = b->data[i];
				max_pos = i;
			}
		}
		
		int rotations = b->top - max_pos;
		if (rotations <= (b->top + 1) / 2)
		{
			while (rotations-- > 0)
				rotate_b(b);
		}
		else
		{
			rotations = max_pos + 1;
			while (rotations-- > 0)
				reverse_rotate_b(b);
		}
		push_btoa(b, a);
	}
}

void	guaranteed_sort(t_stack *a, t_stack *b)
{
	int	size;

	size = a->top + 1;
	rank_normalize(a);
	
	if (size <= 100)
	{
		if (size <= 7)
			optimized_radix_100(a, b);
		else
			fixed_chunk_sort(a, b);
	}
	else if (size <= 500)
	{
		radix_sort(a, b);
	}
	else
	{
		radix_sort(a, b);
	}
}