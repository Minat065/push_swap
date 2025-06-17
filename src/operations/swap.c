/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by student           #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

static void	swap_stack(t_stack *stack)
{
	t_node	*first;
	t_node	*second;

	if (!stack || stack->size < 2)
		return ;
	first = stack->top;
	second = first->next;
	first->next = second->next;
	if (second->next)
		second->next->prev = first;
	else
		stack->bottom = first;
	second->next = first;
	second->prev = NULL;
	first->prev = second;
	stack->top = second;
}

void	sa(t_stack *a, int print)
{
	swap_stack(a);
	if (print)
		write(1, "sa\n", 3);
}

void	sb(t_stack *b, int print)
{
	swap_stack(b);
	if (print)
		write(1, "sb\n", 3);
}

void	ss(t_stack *a, t_stack *b, int print)
{
	swap_stack(a);
	swap_stack(b);
	if (print)
		write(1, "ss\n", 3);
}
