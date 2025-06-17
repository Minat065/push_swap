/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by student           #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

static void	reverse_rotate_stack(t_stack *stack)
{
	t_node	*last;

	if (!stack || stack->size < 2)
		return ;
	last = stack->bottom;
	stack->bottom = last->prev;
	stack->bottom->next = NULL;
	last->prev = NULL;
	last->next = stack->top;
	stack->top->prev = last;
	stack->top = last;
}

void	rra(t_stack *a, int print)
{
	reverse_rotate_stack(a);
	if (print)
		write(1, "rra\n", 4);
}

void	rrb(t_stack *b, int print)
{
	reverse_rotate_stack(b);
	if (print)
		write(1, "rrb\n", 4);
}

void	rrr(t_stack *a, t_stack *b, int print)
{
	reverse_rotate_stack(a);
	reverse_rotate_stack(b);
	if (print)
		write(1, "rrr\n", 4);
}
