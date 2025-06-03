/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_dp_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minato <minato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 22:00:00 by minato            #+#    #+#             */
/*   Updated: 2025/01/06 22:00:00 by minato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"
#include <limits.h>

typedef struct s_move_cost
{
	int		index_a;
	int		index_b;
	int		cost_a;
	int		cost_b;
	int		total_cost;
}	t_move_cost;

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

static t_move_cost	calculate_move_cost_limited(t_stack *a, t_stack *b, int b_pos, int limit)
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
	
	if (cost.total_cost > limit)
		cost.total_cost = INT_MAX;
	
	return (cost);
}

static t_move_cost	find_cheapest_move_optimized(t_stack *a, t_stack *b)
{
	t_move_cost	cheapest;
	t_move_cost	current;
	int			size_b;
	int			i;
	int			search_limit;

	size_b = b->top + 1;
	cheapest.total_cost = INT_MAX;
	
	search_limit = (size_b > 50) ? size_b / 4 : size_b;
	
	i = 0;
	while (i < search_limit)
	{
		current = calculate_move_cost_limited(a, b, i, cheapest.total_cost);
		if (current.total_cost < cheapest.total_cost)
		{
			cheapest = current;
			if (cheapest.total_cost <= 3)
				break;
		}
		i++;
	}
	
	if (cheapest.total_cost == INT_MAX && search_limit < size_b)
	{
		i = search_limit;
		while (i < size_b)
		{
			current = calculate_move_cost_limited(a, b, i, cheapest.total_cost);
			if (current.total_cost < cheapest.total_cost)
				cheapest = current;
			i++;
		}
	}
	
	return (cheapest);
}

static void	internal_rotate_a(t_stack *stack_a)
{
	int i;
	int tmp;

	if (stack_a->top < 1)
		return ;
	i = stack_a->top;
	tmp = stack_a->data[stack_a->top];
	while (i > 0)
	{
		stack_a->data[i] = stack_a->data[i - 1];
		i--;
	}
	stack_a->data[0] = tmp;
}

static void	internal_rotate_b(t_stack *stack_b)
{
	int i;
	int tmp;

	if (stack_b->top < 1)
		return ;
	i = stack_b->top;
	tmp = stack_b->data[stack_b->top];
	while (i > 0)
	{
		stack_b->data[i] = stack_b->data[i - 1];
		i--;
	}
	stack_b->data[0] = tmp;
}

static void	internal_reverse_rotate_a(t_stack *stack_a)
{
	int i;
	int tmp;

	if (stack_a->top < 1)
		return ;
	i = 0;
	tmp = stack_a->data[0];
	while (i < stack_a->top)
	{
		stack_a->data[i] = stack_a->data[i + 1];
		i++;
	}
	stack_a->data[stack_a->top] = tmp;
}

static void	internal_reverse_rotate_b(t_stack *stack_b)
{
	int i;
	int tmp;

	if (stack_b->top < 1)
		return ;
	i = 0;
	tmp = stack_b->data[0];
	while (i < stack_b->top)
	{
		stack_b->data[i] = stack_b->data[i + 1];
		i++;
	}
	stack_b->data[stack_b->top] = tmp;
}

static void	execute_double_rotation(t_stack *a, t_stack *b, 
	int *cost_a, int *cost_b)
{
	while (*cost_a > 0 && *cost_b > 0)
	{
		internal_rotate_a(a);
		internal_rotate_b(b);
		ft_printf("rr\n");
		(*cost_a)--;
		(*cost_b)--;
	}
	while (*cost_a < 0 && *cost_b < 0)
	{
		internal_reverse_rotate_a(a);
		internal_reverse_rotate_b(b);
		ft_printf("rrr\n");
		(*cost_a)++;
		(*cost_b)++;
	}
}

static void	execute_single_rotation(t_stack *stack, int cost, char stack_name)
{
	while (cost > 0)
	{
		if (stack_name == 'a')
			rotate_a(stack);
		else
			rotate_b(stack);
		cost--;
	}
	while (cost < 0)
	{
		if (stack_name == 'a')
			reverse_rotate_a(stack);
		else
			reverse_rotate_b(stack);
		cost++;
	}
}

static void	execute_move(t_stack *a, t_stack *b, t_move_cost move)
{
	execute_double_rotation(a, b, &move.cost_a, &move.cost_b);
	execute_single_rotation(a, move.cost_a, 'a');
	execute_single_rotation(b, move.cost_b, 'b');
	push_btoa(b, a);
}

static void	simple_dp_chunk_push(t_stack *a, t_stack *b)
{
	int	initial_size = a->top + 1;
	int	chunk_size = (initial_size <= 200) ? 28 : 38;
	int	current_chunk = 0;
	
	while (a->top > 2)
	{
		int min_val = current_chunk * chunk_size;
		int max_val = (current_chunk + 1) * chunk_size - 1;
		if (max_val >= initial_size)
			max_val = initial_size - 1;
		
		int moved = 0;
		int target_moves = max_val - min_val + 1;
		int i;
		
		for (i = 0; i < initial_size * 2 && moved < target_moves && a->top > 2; i++)
		{
			if (a->data[a->top] >= min_val && a->data[a->top] <= max_val)
			{
				push_atob(a, b);
				moved++;
			}
			else
				rotate_a(a);
		}
		current_chunk++;
	}
}

static void	final_rotation(t_stack *a)
{
	int		min_pos;
	int		size;
	int		cost;
	int		min_val;
	int		i;

	size = a->top + 1;
	min_pos = 0;
	min_val = INT_MAX;
	i = 0;
	while (i < size)
	{
		if (a->data[i] < min_val)
		{
			min_val = a->data[i];
			min_pos = i;
		}
		i++;
	}
	cost = calculate_rotation_cost(min_pos, size);
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

void	simple_dp_sort(t_stack *a, t_stack *b)
{
	t_move_cost	cheapest;

	rank_normalize(a);
	simple_dp_chunk_push(a, b);
	sort_three(a);
	
	while (b->top >= 0)
	{
		cheapest = find_cheapest_move_optimized(a, b);
		execute_move(a, b, cheapest);
	}
	
	final_rotation(a);
}