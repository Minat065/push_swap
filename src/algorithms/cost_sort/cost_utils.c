/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cost_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by student           #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/push_swap.h"

t_cost	calculate_cost(t_stack *a, t_stack *b, int b_pos)
{
	t_cost	cost;
	int		value;
	int		target_pos;

	initialize_cost(&cost, b_pos);
	if (!a || !b || b_pos < 0 || b_pos >= b->size)
		return (cost);
	value = get_element_at_position(b, b_pos);
	target_pos = find_target_position(a, value);
	calculate_a_moves(&cost, target_pos, a->size);
	calculate_b_moves(&cost, b_pos, b->size);
	calculate_total_cost(&cost);
	return (cost);
}
