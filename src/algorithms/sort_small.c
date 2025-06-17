/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by student           #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

void	sort_two(t_stack *a)
{
	if (!a || a->size != 2 || is_sorted(a))
		return ;
	if (a->top->value > a->top->next->value)
		sa(a, 1);
}

void	sort_three(t_stack *a)
{
	int	first;
	int	second;
	int	third;

	if (!a || a->size != 3 || is_sorted(a))
		return ;
	first = a->top->value;
	second = a->top->next->value;
	third = a->bottom->value;
	if (first > second && second < third && third > first)
		sa(a, 1);
	else if (first > second && second > third)
	{
		sa(a, 1);
		rra(a, 1);
	}
	else if (first > second && second < third && third < first)
		ra(a, 1);
	else if (first < second && second > third && third > first)
	{
		sa(a, 1);
		ra(a, 1);
	}
	else if (first < second && second > third && third < first)
		rra(a, 1);
}

void	sort_four(t_stack *a, t_stack *b)
{
	int	min_pos;

	if (!a || !b || a->size != 4 || is_sorted(a))
		return ;
	min_pos = find_min_position(a);
	smart_rotate_a(a, min_pos);
	pb(a, b, 1);
	sort_three(a);
	pa(a, b, 1);
}

void	sort_five(t_stack *a, t_stack *b)
{
	int	min_pos;

	if (!a || !b || a->size != 5 || is_sorted(a))
		return ;
	min_pos = find_min_position(a);
	smart_rotate_a(a, min_pos);
	pb(a, b, 1);
	sort_four(a, b);
	pa(a, b, 1);
}
