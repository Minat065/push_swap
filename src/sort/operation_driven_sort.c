/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_driven_sort.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minato <minato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 10:00:00 by minato            #+#    #+#             */
/*   Updated: 2025/01/06 10:00:00 by minato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

typedef struct s_move_cost
{
	int		index_a;
	int		index_b;
	int		cost_a;
	int		cost_b;
	int		total_cost;
}	t_move_cost;

static void	rr(t_stack *a, t_stack *b)
{
	rotate_a(a);
	rotate_b(b);
	ft_printf("rr\n");
}

static void	rrr(t_stack *a, t_stack *b)
{
	reverse_rotate_a(a);
	reverse_rotate_b(b);
	ft_printf("rrr\n");
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

static t_move_cost	calculate_move_cost(t_stack *a, t_stack *b, int b_pos)
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

static t_move_cost	find_cheapest_move(t_stack *a, t_stack *b)
{
	t_move_cost	cheapest;
	t_move_cost	current;
	int			size_b;
	int			i;

	size_b = b->top + 1;
	cheapest.total_cost = INT_MAX;
	i = 0;
	while (i < size_b)
	{
		current = calculate_move_cost(a, b, i);
		if (current.total_cost < cheapest.total_cost)
			cheapest = current;
		i++;
	}
	return (cheapest);
}

static void	execute_double_rotation(t_stack *a, t_stack *b, 
	int *cost_a, int *cost_b)
{
	while (*cost_a > 0 && *cost_b > 0)
	{
		rr(a, b);
		(*cost_a)--;
		(*cost_b)--;
	}
	while (*cost_a < 0 && *cost_b < 0)
	{
		rrr(a, b);
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

static void	push_to_b_optimized(t_stack *a, t_stack *b)
{
	int	initial_size;
	int	pushed;

	initial_size = a->top + 1;
	pushed = 0;
	while ((a->top + 1) > 3 && pushed < initial_size - 3)
	{
		push_atob(a, b);
		pushed++;
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

void	operation_driven_sort(t_stack *a, t_stack *b)
{
	t_move_cost	cheapest;

	push_to_b_optimized(a, b);
	sort_three(a);
	while (b->top >= 0)
	{
		cheapest = find_cheapest_move(a, b);
		execute_move(a, b, cheapest);
	}
	final_rotation(a);
}