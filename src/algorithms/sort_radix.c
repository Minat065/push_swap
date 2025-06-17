/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_radix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by student           #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

void	assign_indices(t_stack *stack)
{
	t_node	*current;
	t_node	*compare;
	int		index;

	if (!stack)
		return ;
	current = stack->top;
	while (current)
	{
		index = 0;
		compare = stack->top;
		while (compare)
		{
			if (compare->value < current->value)
				index++;
			compare = compare->next;
		}
		current->index = index;
		current = current->next;
	}
}

int	get_max_bits(t_stack *stack)
{
	int		max_index;
	int		bits;
	t_node	*current;

	if (!stack || stack->size == 0)
		return (0);
	max_index = 0;
	current = stack->top;
	while (current)
	{
		if (current->index > max_index)
			max_index = current->index;
		current = current->next;
	}
	bits = 0;
	while ((max_index >> bits) != 0)
		bits++;
	if (bits == 0)
		bits = 1;
	return (bits);
}

static void	process_bit_sorting(t_stack *a, t_stack *b, int bit)
{
	int	i;
	int	size;

	i = 0;
	size = a->size;
	while (i < size)
	{
		if (((a->top->index >> bit) & 1) == 0)
			pb(a, b, 1);
		else
			ra(a, 1);
		i++;
	}
	while (b->size > 0)
		pa(a, b, 1);
}

void	radix_sort(t_stack *a, t_stack *b)
{
	int	max_bits;
	int	bit;

	if (!a || !b || a->size <= 1)
		return ;
	assign_indices(a);
	max_bits = get_max_bits(a);
	bit = 0;
	while (bit < max_bits)
	{
		process_bit_sorting(a, b, bit);
		bit++;
	}
}
