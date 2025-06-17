/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by student           #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

static void	push_node(t_stack *from, t_stack *to)
{
	t_node	*node;

	if (!from || from->size == 0)
		return ;
	node = from->top;
	from->top = node->next;
	if (from->top)
		from->top->prev = NULL;
	else
		from->bottom = NULL;
	from->size--;
	node->next = to->top;
	node->prev = NULL;
	if (to->top)
		to->top->prev = node;
	else
		to->bottom = node;
	to->top = node;
	to->size++;
}

void	pa(t_stack *a, t_stack *b, int print)
{
	push_node(b, a);
	if (print)
		write(1, "pa\n", 3);
}

void	pb(t_stack *a, t_stack *b, int print)
{
	push_node(a, b);
	if (print)
		write(1, "pb\n", 3);
}
