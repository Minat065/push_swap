/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cost_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by student           #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/push_swap.h"

void	cost_sort(t_stack *a, t_stack *b)
{
	t_cost	cheapest;
	int		min_pos;

	if (!a || !b || a->size <= 3)
		return ;
	if (is_sorted(a))
		return ;
	while (a->size > 3)
		pb(a, b, 1);
	sort_three(a);
	while (b->size > 0)
	{
		cheapest = find_cheapest_move(a, b);
		execute_moves(a, b, cheapest);
	}
	min_pos = find_min_position(a);
	smart_rotate_a(a, min_pos);
}

void	cost_sort_optimized(t_stack *a, t_stack *b)
{
	t_cost	cheapest;
	int		min_pos;

	if (!a || !b || a->size <= 3)
		return ;
	if (is_sorted(a))
		return ;
	smart_push_large(a, b);
	sort_three(a);
	while (b->size > 0)
	{
		cheapest = find_cheapest_move(a, b);
		execute_moves(a, b, cheapest);
	}
	min_pos = find_min_position(a);
	smart_rotate_a(a, min_pos);
}
