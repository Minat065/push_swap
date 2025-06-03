/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precision_cost_sort.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minato <minato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:00:00 by minato            #+#    #+#             */
/*   Updated: 2025/01/06 19:00:00 by minato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

typedef struct s_precise_cost
{
	int		b_index;
	int		a_insert_pos;
	int		b_rotations;
	int		a_rotations;
	int		total_ops;
	int		future_penalty;
}	t_precise_cost;

static int	get_stack_position(t_stack *stack, int index)
{
	return (stack->top - index);
}

static int	calculate_precise_rotations(int position, int stack_size)
{
	int	forward = position;
	int	backward = stack_size - position;
	
	return (forward <= backward) ? forward : backward;
}

static int	find_precise_insert_position(t_stack *a, int value)
{
	int	size = a->top + 1;
	int	best_pos = 0;
	int	min_greater = INT_MAX;
	int	max_smaller = INT_MIN;
	int	max_pos = 0;
	int	i;

	if (size == 0)
		return (0);

	for (i = 0; i <= a->top; i++)
	{
		int stack_pos = get_stack_position(a, i);
		
		if (a->data[i] > value && a->data[i] < min_greater)
		{
			min_greater = a->data[i];
			best_pos = stack_pos;
		}
		
		if (a->data[i] < value && a->data[i] > max_smaller)
		{
			max_smaller = a->data[i];
		}
		
		if (a->data[i] > a->data[max_pos])
			max_pos = i;
	}
	
	if (min_greater == INT_MAX)
	{
		best_pos = get_stack_position(a, max_pos);
	}
	
	return (best_pos);
}

static int	calculate_future_penalty(t_stack *a, t_stack *b, int b_pos, int value)
{
	int	penalty = 0;
	int	nearby_elements = 0;
	int	i;
	
	for (i = 0; i <= b->top && i < 10; i++)
	{
		if (i == b_pos)
			continue;
			
		int diff = (b->data[i] > value) ? b->data[i] - value : value - b->data[i];
		if (diff < 50)
		{
			nearby_elements++;
			if (i < b_pos)
				penalty += 2;
			else
				penalty += 1;
		}
	}
	
	int a_size = a->top + 1;
	if (a_size > 0)
	{
		for (i = 0; i <= a->top && i < 5; i++)
		{
			int diff = (a->data[i] > value) ? a->data[i] - value : value - a->data[i];
			if (diff < 20)
				penalty -= 1;
		}
	}
	
	return (penalty);
}

static t_precise_cost	calculate_precise_cost(t_stack *a, t_stack *b, int b_pos)
{
	t_precise_cost	cost;
	int				value;
	int				b_stack_pos;
	int				a_stack_pos;

	value = b->data[b_pos];
	b_stack_pos = get_stack_position(b, b_pos);
	a_stack_pos = find_precise_insert_position(a, value);
	
	cost.b_index = b_pos;
	cost.a_insert_pos = a_stack_pos;
	cost.b_rotations = calculate_precise_rotations(b_stack_pos, b->top + 1);
	cost.a_rotations = calculate_precise_rotations(a_stack_pos, a->top + 1);
	
	int same_direction = ((b_stack_pos <= (b->top + 1) / 2) == 
						  (a_stack_pos <= (a->top + 1) / 2));
	
	if (same_direction)
	{
		cost.total_ops = (cost.a_rotations > cost.b_rotations) ? 
						 cost.a_rotations : cost.b_rotations;
	}
	else
	{
		cost.total_ops = cost.a_rotations + cost.b_rotations;
	}
	
	cost.total_ops += 1;
	
	cost.future_penalty = calculate_future_penalty(a, b, b_pos, value);
	cost.total_ops += cost.future_penalty;
	
	return (cost);
}

static t_precise_cost	find_optimal_move(t_stack *a, t_stack *b)
{
	t_precise_cost	best;
	t_precise_cost	current;
	int				b_size;
	int				search_limit;
	int				i;

	b_size = b->top + 1;
	best.total_ops = INT_MAX;
	
	search_limit = (b_size > 40) ? 20 : b_size;
	
	for (i = 0; i < search_limit; i++)
	{
		current = calculate_precise_cost(a, b, i);
		if (current.total_ops < best.total_ops)
		{
			best = current;
			if (best.total_ops <= 1)
				break;
		}
	}
	
	if (best.total_ops > 8 && search_limit < b_size)
	{
		for (i = search_limit; i < b_size && i < search_limit * 2; i++)
		{
			current = calculate_precise_cost(a, b, i);
			if (current.total_ops < best.total_ops)
				best = current;
		}
	}
	
	return (best);
}

static void	execute_precise_move(t_stack *a, t_stack *b, t_precise_cost move)
{
	int	b_stack_pos = get_stack_position(b, move.b_index);
	int	a_stack_pos = move.a_insert_pos;
	int	b_size = b->top + 1;
	int	a_size = a->top + 1;
	
	int	b_forward = (b_stack_pos <= b_size / 2);
	int	a_forward = (a_stack_pos <= a_size / 2);
	
	int	b_rots = b_forward ? b_stack_pos : b_size - b_stack_pos;
	int	a_rots = a_forward ? a_stack_pos : a_size - a_stack_pos;
	
	if (b_forward == a_forward)
	{
		while (b_rots > 0 && a_rots > 0)
		{
			if (b_forward)
			{
				rotate_a(a);
				rotate_b(b);
				ft_printf("rr\n");
			}
			else
			{
				reverse_rotate_a(a);
				reverse_rotate_b(b);
				ft_printf("rrr\n");
			}
			b_rots--;
			a_rots--;
		}
	}
	
	while (b_rots > 0)
	{
		if (b_forward)
			rotate_b(b);
		else
			reverse_rotate_b(b);
		b_rots--;
	}
	
	while (a_rots > 0)
	{
		if (a_forward)
			rotate_a(a);
		else
			reverse_rotate_a(a);
		a_rots--;
	}
	
	push_btoa(b, a);
}

static void	intelligent_chunk_push(t_stack *a, t_stack *b)
{
	int	initial_size = a->top + 1;
	int	chunk_size = (initial_size <= 100) ? 22 : 
					 (initial_size <= 300) ? 30 : 33;
	int	current_chunk = 0;
	
	while (a->top > 2)
	{
		int min_val = current_chunk * chunk_size;
		int max_val = (current_chunk + 1) * chunk_size - 1;
		if (max_val >= initial_size)
			max_val = initial_size - 1;
		
		int moved = 0;
		int target_moves = max_val - min_val + 1;
		int rotation_count = 0;
		
		while (moved < target_moves && a->top > 2 && rotation_count < initial_size * 2)
		{
			if (a->data[a->top] >= min_val && a->data[a->top] <= max_val)
			{
				push_atob(a, b);
				moved++;
				rotation_count = 0;
				
				if (b->top > 0)
				{
					int threshold = min_val + (max_val - min_val) / 4;
					if (b->data[b->top] < threshold)
						rotate_b(b);
				}
			}
			else
			{
				rotate_a(a);
				rotation_count++;
			}
		}
		current_chunk++;
	}
}

static void	final_positioning(t_stack *a)
{
	int	min_val = INT_MAX;
	int	min_index = 0;
	int	size = a->top + 1;
	int	i;
	
	for (i = 0; i <= a->top; i++)
	{
		if (a->data[i] < min_val)
		{
			min_val = a->data[i];
			min_index = i;
		}
	}
	
	int	min_pos = get_stack_position(a, min_index);
	int	rotations = calculate_precise_rotations(min_pos, size);
	int forward = (min_pos <= size / 2);
	
	while (rotations-- > 0)
	{
		if (forward)
			rotate_a(a);
		else
			reverse_rotate_a(a);
	}
}

void	precision_cost_sort(t_stack *a, t_stack *b)
{
	rank_normalize(a);
	intelligent_chunk_push(a, b);
	sort_three(a);
	
	while (b->top >= 0)
	{
		t_precise_cost optimal = find_optimal_move(a, b);
		execute_precise_move(a, b, optimal);
	}
	
	final_positioning(a);
}