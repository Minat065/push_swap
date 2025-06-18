/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cost_calculation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by student           #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/push_swap.h"

void	initialize_cost(t_cost *cost, int b_pos)
{
	cost->b_index = b_pos;
	cost->a_moves = 0;
	cost->b_moves = 0;
	cost->total = 0;
}

void	calculate_a_moves(t_cost *cost, int target_pos, int a_size)
{
	if (target_pos <= a_size / 2)
		cost->a_moves = target_pos;
	else
		cost->a_moves = -(a_size - target_pos);
}

void	calculate_b_moves(t_cost *cost, int b_pos, int b_size)
{
	if (b_pos <= b_size / 2)
		cost->b_moves = b_pos;
	else
		cost->b_moves = -(b_size - b_pos);
}

void	calculate_abs_values(t_cost *cost, int *abs_a, int *abs_b)
{
	if (cost->a_moves < 0)
		*abs_a = -cost->a_moves;
	else
		*abs_a = cost->a_moves;
	if (cost->b_moves < 0)
		*abs_b = -cost->b_moves;
	else
		*abs_b = cost->b_moves;
}

void	calculate_total_cost(t_cost *cost)
{
	int	abs_a;
	int	abs_b;

	if (cost->a_moves >= 0 && cost->b_moves >= 0)
	{
		if (cost->a_moves > cost->b_moves)
			cost->total = cost->a_moves;
		else
			cost->total = cost->b_moves;
	}
	else if (cost->a_moves < 0 && cost->b_moves < 0)
	{
		abs_a = -cost->a_moves;
		abs_b = -cost->b_moves;
		if (abs_a > abs_b)
			cost->total = abs_a;
		else
			cost->total = abs_b;
	}
	else
	{
		calculate_abs_values(cost, &abs_a, &abs_b);
		cost->total = abs_a + abs_b;
	}
}
