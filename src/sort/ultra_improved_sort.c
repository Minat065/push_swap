/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ultra_improved_sort.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minato <minato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 18:00:00 by minato            #+#    #+#             */
/*   Updated: 2025/01/06 18:00:00 by minato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

#define MAX_B_SIZE 120
#define FALLBACK_THRESHOLD 15000

typedef struct s_move_cost
{
	int		index_a;
	int		index_b;
	int		cost_a;
	int		cost_b;
	int		total_cost;
}	t_move_cost;

static int	operation_count = 0;

static void	count_operation(void)
{
	operation_count++;
}

static int	calculate_rotation_cost(int position, int size)
{
	int	forward_cost;
	int	backward_cost;

	forward_cost = position;
	backward_cost = size - position;
	if (forward_cost <= backward_cost)
		return (forward_cost);
	return (-backward_cost);
}

static int	find_insert_position(t_stack *a, int value)
{
	int		size;
	int		min_pos;
	int		min_val;
	int		i;

	size = a->top + 1;
	if (size == 0)
		return (0);
	min_pos = 0;
	min_val = INT_MAX;
	i = 0;
	while (i < size)
	{
		if (a->data[i] > value && a->data[i] < min_val)
		{
			min_val = a->data[i];
			min_pos = i;
		}
		i++;
	}
	if (min_val == INT_MAX)
	{
		min_val = INT_MIN;
		i = 0;
		while (i < size)
		{
			if (a->data[i] > min_val)
			{
				min_val = a->data[i];
				min_pos = i;
			}
			i++;
		}
	}
	return (min_pos);
}

static int	analyze_distribution(t_stack *a, int start, int end)
{
	int	count = 0;
	int	i;
	int	size = a->top + 1;

	for (i = 0; i < size; i++)
	{
		if (a->data[i] >= start && a->data[i] <= end)
			count++;
	}
	return (count);
}

static int	get_adaptive_chunk_size(t_stack *a, int total_size)
{
	int	base_chunk_size;
	int	test_chunk_size;
	int	best_chunk_size;
	int	min_variance;
	int	variance;
	int	i;

	base_chunk_size = (total_size <= 200) ? 30 : 40;
	best_chunk_size = base_chunk_size;
	min_variance = INT_MAX;
	
	for (test_chunk_size = base_chunk_size - 10; 
		 test_chunk_size <= base_chunk_size + 10; 
		 test_chunk_size += 5)
	{
		if (test_chunk_size <= 15)
			continue;
			
		variance = 0;
		int chunks = (total_size + test_chunk_size - 1) / test_chunk_size;
		
		for (i = 0; i < chunks; i++)
		{
			int start = i * test_chunk_size;
			int end = (i + 1) * test_chunk_size - 1;
			if (end >= total_size)
				end = total_size - 1;
			
			int count = analyze_distribution(a, start, end);
			int expected = test_chunk_size;
			if (end >= total_size - 1)
				expected = total_size - start;
			
			variance += (count - expected) * (count - expected);
		}
		
		if (variance < min_variance)
		{
			min_variance = variance;
			best_chunk_size = test_chunk_size;
		}
	}
	
	return (best_chunk_size);
}

static t_move_cost	calculate_move_cost_fast(t_stack *a, t_stack *b, int b_pos)
{
	t_move_cost	cost;
	int			value;

	value = b->data[b_pos];
	cost.index_b = b_pos;
	cost.index_a = find_insert_position(a, value);
	cost.cost_b = calculate_rotation_cost(b_pos, b->top + 1);
	cost.cost_a = calculate_rotation_cost(cost.index_a, a->top + 1);
	
	if ((cost.cost_a > 0 && cost.cost_b > 0) || 
		(cost.cost_a < 0 && cost.cost_b < 0))
	{
		if (cost.cost_a > 0)
			cost.total_cost = (cost.cost_a > cost.cost_b) ? 
				cost.cost_a : cost.cost_b;
		else
			cost.total_cost = (cost.cost_a < cost.cost_b) ? 
				-cost.cost_a : -cost.cost_b;
	}
	else
	{
		cost.total_cost = ((cost.cost_a > 0) ? cost.cost_a : -cost.cost_a) +
			((cost.cost_b > 0) ? cost.cost_b : -cost.cost_b);
	}
	cost.total_cost++;
	
	return (cost);
}

static t_move_cost	find_cheapest_move_limited(t_stack *a, t_stack *b)
{
	t_move_cost	cheapest;
	t_move_cost	current;
	int			size_b;
	int			search_limit;
	int			i;

	size_b = b->top + 1;
	cheapest.total_cost = INT_MAX;
	
	if (size_b <= 20)
		search_limit = size_b;
	else if (size_b <= 100)
		search_limit = size_b / 2;
	else
		search_limit = size_b / 4;
	
	for (i = 0; i < search_limit; i++)
	{
		current = calculate_move_cost_fast(a, b, i);
		if (current.total_cost < cheapest.total_cost)
		{
			cheapest = current;
			if (cheapest.total_cost <= 2)
				break;
		}
	}
	
	if (cheapest.total_cost > 10 && search_limit < size_b)
	{
		for (i = search_limit; i < size_b && i < search_limit * 2; i++)
		{
			current = calculate_move_cost_fast(a, b, i);
			if (current.total_cost < cheapest.total_cost)
				cheapest = current;
		}
	}
	
	return (cheapest);
}

static void	execute_move_with_count(t_stack *a, t_stack *b, t_move_cost move)
{
	int	cost_a = move.cost_a;
	int	cost_b = move.cost_b;
	
	while (cost_a > 0 && cost_b > 0)
	{
		rotate_a(a);
		rotate_b(b);
		ft_printf("rr\n");
		cost_a--;
		cost_b--;
		count_operation();
	}
	while (cost_a < 0 && cost_b < 0)
	{
		reverse_rotate_a(a);
		reverse_rotate_b(b);
		ft_printf("rrr\n");
		cost_a++;
		cost_b++;
		count_operation();
	}
	
	while (cost_a > 0)
	{
		rotate_a(a);
		cost_a--;
		count_operation();
	}
	while (cost_a < 0)
	{
		reverse_rotate_a(a);
		cost_a++;
		count_operation();
	}
	while (cost_b > 0)
	{
		rotate_b(b);
		cost_b--;
		count_operation();
	}
	while (cost_b < 0)
	{
		reverse_rotate_b(b);
		cost_b++;
		count_operation();
	}
	
	push_btoa(b, a);
	count_operation();
}

static void	staged_push_back(t_stack *a, t_stack *b, int max_elements)
{
	int	processed = 0;
	t_move_cost	cheapest;

	while (b->top >= 0 && processed < max_elements)
	{
		if (operation_count > FALLBACK_THRESHOLD)
			break;
			
		cheapest = find_cheapest_move_limited(a, b);
		execute_move_with_count(a, b, cheapest);
		processed++;
	}
}

static void	smart_staged_push(t_stack *a, t_stack *b)
{
	int	initial_size;
	int	chunk_size;
	int	current_chunk;
	int	i;

	initial_size = a->top + 1;
	chunk_size = get_adaptive_chunk_size(a, initial_size);
	current_chunk = 0;
	
	while (a->top > 2)
	{
		int min_chunk = current_chunk * chunk_size;
		int max_chunk = (current_chunk + 1) * chunk_size - 1;
		if (max_chunk >= initial_size)
			max_chunk = initial_size - 1;
			
		int moved = 0;
		int max_moves = max_chunk - min_chunk + 1;
		
		for (i = 0; i < initial_size * 2 && moved < max_moves && a->top > 2; i++)
		{
			if (operation_count > FALLBACK_THRESHOLD)
				return;
				
			if (a->data[a->top] >= min_chunk && a->data[a->top] <= max_chunk)
			{
				push_atob(a, b);
				count_operation();
				moved++;
				
				if (b->top > 0 && b->data[b->top] < min_chunk + (max_chunk - min_chunk) / 3)
				{
					rotate_b(b);
					count_operation();
				}
			}
			else
			{
				rotate_a(a);
				count_operation();
			}
		}
		
		if ((b->top + 1) >= MAX_B_SIZE)
		{
			staged_push_back(a, b, MAX_B_SIZE / 3);
		}
		
		current_chunk++;
	}
}

static void	fallback_to_simple_sort(t_stack *a, t_stack *b)
{
	while (b->top >= 0)
	{
		int max_pos = 0;
		int max_val = b->data[0];
		int i;
		
		for (i = 1; i <= b->top; i++)
		{
			if (b->data[i] > max_val)
			{
				max_val = b->data[i];
				max_pos = i;
			}
		}
		
		max_pos = b->top - max_pos;
		int size_b = b->top + 1;
		
		if (max_pos <= size_b / 2)
		{
			while (max_pos-- > 0)
				rotate_b(b);
		}
		else
		{
			int rev_rotations = size_b - max_pos;
			while (rev_rotations-- > 0)
				reverse_rotate_b(b);
		}
		push_btoa(b, a);
	}
}

void	ultra_improved_sort(t_stack *a, t_stack *b)
{
	operation_count = 0;
	
	rank_normalize(a);
	smart_staged_push(a, b);
	sort_three(a);
	
	if (operation_count > FALLBACK_THRESHOLD)
	{
		fallback_to_simple_sort(a, b);
	}
	else
	{
		while (b->top >= 0)
		{
			if (operation_count > FALLBACK_THRESHOLD)
			{
				fallback_to_simple_sort(a, b);
				break;
			}
			
			t_move_cost cheapest = find_cheapest_move_limited(a, b);
			execute_move_with_count(a, b, cheapest);
		}
	}
	
	int min_pos = 0;
	int min_val = INT_MAX;
	int size = a->top + 1;
	int i;
	
	for (i = 0; i < size; i++)
	{
		if (a->data[i] < min_val)
		{
			min_val = a->data[i];
			min_pos = i;
		}
	}
	
	int cost = calculate_rotation_cost(min_pos, size);
	if (cost > 0)
	{
		while (cost-- > 0)
			rotate_a(a);
	}
	else
	{
		while (cost++ < 0)
			reverse_rotate_a(a);
	}
}