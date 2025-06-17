/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by student           #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

static void	rotate_stack(t_stack *stack)
{
	t_node	*first;

	if (!stack || stack->size < 2)
		return ;
	first = stack->top;
	stack->top = first->next;
	stack->top->prev = NULL;
	first->next = NULL;
	first->prev = stack->bottom;
	stack->bottom->next = first;
	stack->bottom = first;
}

void	ra(t_stack *a, int print)
{
	rotate_stack(a);
	if (print)
		write(1, "ra\n", 3);
}

void	rb(t_stack *b, int print)
{
	rotate_stack(b);
	if (print)
		write(1, "rb\n", 3);
}

void	rr(t_stack *a, t_stack *b, int print)
{
	rotate_stack(a);
	rotate_stack(b);
	if (print)
		write(1, "rr\n", 3);
}
