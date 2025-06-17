/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_helpers2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by student           #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

static int	find_smallest_greater(t_stack *a, int value, int *target_pos)
{
	t_node	*current;
	int		pos;
	int		target_value;

	current = a->top;
	pos = 0;
	*target_pos = 0;
	target_value = current->value;
	while (current)
	{
		if (current->value > value && current->value < target_value)
		{
			target_value = current->value;
			*target_pos = pos;
		}
		current = current->next;
		pos++;
	}
	return (target_value);
}

int	find_target_in_a(t_stack *a, int value)
{
	int	target_pos;
	int	target_value;
	int	max_pos;

	if (a->size == 0)
		return (0);
	target_value = find_smallest_greater(a, value, &target_pos);
	if (target_value == a->top->value && a->top->value <= value)
	{
		max_pos = find_max_position(a);
		return ((max_pos + 1) % a->size);
	}
	return (target_pos);
}

static int	find_smallest_larger(t_stack *a, int value, int *target_pos)
{
	t_node	*current;
	int		pos;
	int		target_value;

	current = a->top;
	pos = 0;
	*target_pos = 0;
	target_value = INT_MAX;
	while (current)
	{
		if (current->value > value && current->value < target_value)
		{
			target_value = current->value;
			*target_pos = pos;
		}
		current = current->next;
		pos++;
	}
	return (target_value);
}

int	find_target_position(t_stack *a, int value)
{
	int	target_pos;
	int	target_value;

	if (!a || a->size == 0)
		return (0);
	target_value = find_smallest_larger(a, value, &target_pos);
	if (target_value == INT_MAX)
	{
		target_pos = find_max_position(a);
		target_pos = (target_pos + 1) % a->size;
	}
	return (target_pos);
}

int	get_element_at_position(t_stack *stack, int pos)
{
	t_node	*current;
	int		i;

	if (!stack || pos < 0 || pos >= stack->size)
		return (0);
	current = stack->top;
	i = 0;
	while (i < pos && current)
	{
		current = current->next;
		i++;
	}
	if (current)
		return (current->value);
	return (0);
}
