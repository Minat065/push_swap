/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by student           #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

static void	process_small_element(t_stack *a, t_stack *b, int *push_count,
						int median)
{
	pb(a, b, 1);
	(*push_count)--;
	if (b->size > 1 && b->top->index < median / 2)
		rb(b, 1);
}

void	push_small_elements(t_stack *a, t_stack *b, int *push_count,
				int median)
{
	int	rotations;

	rotations = 0;
	while (*push_count > 0 && a->size > 3 && rotations < a->size)
	{
		if (a->top->index < median)
		{
			process_small_element(a, b, push_count, median);
			rotations = 0;
		}
		else
		{
			ra(a, 1);
			rotations++;
		}
	}
}
