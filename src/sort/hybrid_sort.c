/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hybrid_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minato <minato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:00:00 by minato            #+#    #+#             */
/*   Updated: 2025/01/06 14:00:00 by minato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

typedef struct s_cost_info
{
	int	position;
	int	value;
	int	rotation_cost;
	int	push_location;
}	t_cost_info;

static int	calculate_rotation_cost(int position, int size)
{
	int	forward;
	int	backward;

	forward = position;
	backward = size - position;
	return ((forward <= backward) ? forward : backward);
}

static void	smart_rotate(t_stack *stack, int position, char stack_name)
{
	int	size;
	int	forward;
	int	backward;

	size = stack->top + 1;
	forward = position;
	backward = size - position;
	
	if (forward <= backward)
	{
		while (forward-- > 0)
		{
			if (stack_name == 'a')
				rotate_a(stack);
			else
				rotate_b(stack);
		}
	}
	else
	{
		while (backward-- > 0)
		{
			if (stack_name == 'a')
				reverse_rotate_a(stack);
			else
				reverse_rotate_b(stack);
		}
	}
}

static void	push_chunks_with_cost_analysis(t_stack *a, t_stack *b)
{
	int	size;
	int	chunk_size;
	int	current_chunk;
	int	i;
	int	j;

	size = a->top + 1;
	if (size <= 20)
		chunk_size = 7;
	else if (size <= 50)
		chunk_size = 10;
	else if (size <= 100)
		chunk_size = 12;
	else if (size <= 200)
		chunk_size = 20;
	else
		chunk_size = 30;
		
	current_chunk = 0;
	while (a->top >= 0)
	{
		int min_val = current_chunk * chunk_size;
		int max_val = (current_chunk + 1) * chunk_size - 1;
		int chunk_count = 0;
		
		if (max_val >= size)
		{
			max_val = size - 1;
		}
		
		i = 0;
		while (i <= a->top)
		{
			if (a->data[i] >= min_val && a->data[i] <= max_val)
				chunk_count++;
			i++;
		}
		
		if (chunk_count == 0)
		{
			current_chunk++;
			continue;
		}
		
		j = 0;
		while (j < chunk_count && a->top >= 0)
		{
			int best_pos = -1;
			int best_cost = INT_MAX;
			
			i = 0;
			while (i <= a->top)
			{
				if (a->data[a->top - i] >= min_val && 
					a->data[a->top - i] <= max_val)
				{
					int cost = calculate_rotation_cost(i, a->top + 1);
					if (cost < best_cost)
					{
						best_cost = cost;
						best_pos = i;
					}
				}
				i++;
			}
			
			if (best_pos != -1)
			{
				smart_rotate(a, best_pos, 'a');
				push_atob(a, b);
				
				if (b->top > 0)
				{
					int val = b->data[b->top];
					int threshold = min_val + (max_val - min_val) / 3;
					if (val < threshold && b->data[b->top - 1] > val)
						rotate_b(b);
				}
				j++;
			}
			else
				break;
		}
		current_chunk++;
	}
}

static void	optimized_push_back(t_stack *a, t_stack *b)
{
	while (b->top >= 0)
	{
		int max_val = INT_MIN;
		int max_pos = -1;
		int second_max = INT_MIN;
		int second_pos = -1;
		int i;
		
		i = 0;
		while (i <= b->top)
		{
			if (b->data[i] > max_val)
			{
				second_max = max_val;
				second_pos = max_pos;
				max_val = b->data[i];
				max_pos = i;
			}
			else if (b->data[i] > second_max)
			{
				second_max = b->data[i];
				second_pos = i;
			}
			i++;
		}
		
		max_pos = b->top - max_pos;
		if (second_pos != -1)
			second_pos = b->top - second_pos;
		
		if (b->top > 0 && second_pos != -1)
		{
			int cost_max = calculate_rotation_cost(max_pos, b->top + 1);
			int cost_second = calculate_rotation_cost(second_pos, b->top + 1);
			
			if (cost_second < cost_max && second_pos == 1)
			{
				swap_b(b);
				push_btoa(b, a);
				continue;
			}
		}
		
		smart_rotate(b, max_pos, 'b');
		push_btoa(b, a);
	}
}

static void	insertion_finish(t_stack *a, t_stack *b)
{
	while (b->top >= 0)
	{
		int	best_pos = 0;
		int	best_cost = INT_MAX;
		int	b_val = b->data[b->top];
		int	i;
		
		i = 0;
		while (i <= a->top)
		{
			int a_val = a->data[a->top - i];
			int next_val = (i == a->top) ? a->data[0] : a->data[a->top - i - 1];
			
			if ((a_val < b_val && b_val < next_val) ||
				(a_val > next_val && (b_val > a_val || b_val < next_val)))
			{
				int cost = calculate_rotation_cost(i, a->top + 1);
				if (cost < best_cost)
				{
					best_cost = cost;
					best_pos = i;
				}
			}
			i++;
		}
		
		if (best_cost == INT_MAX)
		{
			int min_pos = 0;
			int min_val = INT_MAX;
			i = 0;
			while (i <= a->top)
			{
				if (a->data[i] < min_val)
				{
					min_val = a->data[i];
					min_pos = a->top - i;
				}
				i++;
			}
			best_pos = min_pos;
		}
		
		smart_rotate(a, best_pos, 'a');
		push_btoa(b, a);
	}
	
	int min_pos = 0;
	int min_val = INT_MAX;
	int i = 0;
	while (i <= a->top)
	{
		if (a->data[i] < min_val)
		{
			min_val = a->data[i];
			min_pos = a->top - i;
		}
		i++;
	}
	smart_rotate(a, min_pos, 'a');
}

void	hybrid_sort(t_stack *a, t_stack *b)
{
	int	size;

	size = a->top + 1;
	rank_normalize(a);
	
	if (size <= 5)
	{
		if (size == 2)
			sort_two(a);
		else if (size == 3)
			sort_three(a);
		else if (size == 4)
			sort_four(a, b);
		else if (size == 5)
			sort_five(a, b);
		return;
	}
	
	push_chunks_with_cost_analysis(a, b);
	
	if (b->top < 50)
		insertion_finish(a, b);
	else
		optimized_push_back(a, b);
}