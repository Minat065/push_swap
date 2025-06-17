/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_chunk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by student           #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

int	get_chunk_size(int total_size)
{
	if (total_size <= 10)
		return (2);
	else if (total_size <= 50)
		return (5);
	else if (total_size <= 100)
		return (15);
	else if (total_size <= 500)
		return (35);
	else
		return (50);
}

static void	push_chunk_elements(t_stack *a, t_stack *b, int chunk_min,
						int chunk_max)
{
	int	pushed;
	int	rotations;
	int	chunk_size;

	chunk_size = chunk_max - chunk_min + 1;
	pushed = 0;
	rotations = 0;
	while (pushed < chunk_size && rotations < a->size)
	{
		if (a->top->index >= chunk_min && a->top->index <= chunk_max)
		{
			pb(a, b, 1);
			pushed++;
			if (b->size > 1 && b->top->index < chunk_min + chunk_size / 2)
				rb(b, 1);
			rotations = 0;
		}
		else
		{
			ra(a, 1);
			rotations++;
		}
	}
}

void	push_chunks_to_b(t_stack *a, t_stack *b, int chunk_size)
{
	int	chunk_min;
	int	chunk_max;

	chunk_min = 0;
	while (a->size > 3)
	{
		chunk_max = chunk_min + chunk_size - 1;
		push_chunk_elements(a, b, chunk_min, chunk_max);
		chunk_min += chunk_size;
	}
}

void	sort_b_to_a(t_stack *a, t_stack *b)
{
	int	max_pos;
	int	target_pos;

	while (b->size > 0)
	{
		max_pos = find_max_position(b);
		smart_rotate_b(b, max_pos);
		target_pos = find_target_in_a(a, b->top->value);
		smart_rotate_a(a, target_pos);
		pa(a, b, 1);
	}
}

void	chunk_sort(t_stack *a, t_stack *b)
{
	int	chunk_size;

	if (!a || !b || a->size <= 3)
		return ;
	if (is_sorted(a))
		return ;
	assign_indices(a);
	chunk_size = get_chunk_size(a->size);
	push_chunks_to_b(a, b, chunk_size);
	sort_three(a);
	sort_b_to_a(a, b);
}
