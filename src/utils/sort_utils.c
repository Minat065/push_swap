/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by student           #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

int	find_min_position(t_stack *stack)
{
	t_node	*current;
	int		min_value;
	int		min_pos;
	int		pos;

	if (!stack || stack->size == 0)
		return (-1);
	current = stack->top;
	min_value = current->value;
	min_pos = 0;
	pos = 0;
	while (current)
	{
		if (current->value < min_value)
		{
			min_value = current->value;
			min_pos = pos;
		}
		current = current->next;
		pos++;
	}
	return (min_pos);
}

int	find_max_position(t_stack *stack)
{
	t_node	*current;
	int		max_value;
	int		max_pos;
	int		pos;

	if (!stack || stack->size == 0)
		return (-1);
	current = stack->top;
	max_value = current->value;
	max_pos = 0;
	pos = 0;
	while (current)
	{
		if (current->value > max_value)
		{
			max_value = current->value;
			max_pos = pos;
		}
		current = current->next;
		pos++;
	}
	return (max_pos);
}

void	smart_rotate_a(t_stack *a, int position)
{
	if (!a || position < 0 || position >= a->size)
		return ;
	if (position == 0)
		return ;
	if (position <= a->size / 2)
	{
		while (position > 0)
		{
			ra(a, 1);
			position--;
		}
	}
	else
	{
		position = a->size - position;
		while (position > 0)
		{
			rra(a, 1);
			position--;
		}
	}
}

void	smart_rotate_b(t_stack *b, int position)
{
	if (!b || position < 0 || position >= b->size)
		return ;
	if (position == 0)
		return ;
	if (position <= b->size / 2)
	{
		while (position > 0)
		{
			rb(b, 1);
			position--;
		}
	}
	else
	{
		position = b->size - position;
		while (position > 0)
		{
			rrb(b, 1);
			position--;
		}
	}
}

t_cost	find_cheapest_move(t_stack *a, t_stack *b)
{
	t_cost	cheapest;
	t_cost	current;
	int		i;

	cheapest.total = INT_MAX;
	i = 0;
	while (i < b->size)
	{
		current = calculate_cost(a, b, i);
		if (current.total < cheapest.total)
			cheapest = current;
		i++;
	}
	return (cheapest);
}
