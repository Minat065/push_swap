/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by student           #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/push_swap.h"

static void	execute_simultaneous_moves(t_stack *a, t_stack *b, int *a_moves,
						int *b_moves)
{
	while (*a_moves > 0 && *b_moves > 0)
	{
		rr(a, b, 1);
		(*a_moves)--;
		(*b_moves)--;
	}
	while (*a_moves < 0 && *b_moves < 0)
	{
		rrr(a, b, 1);
		(*a_moves)++;
		(*b_moves)++;
	}
}

static void	execute_a_moves(t_stack *a, int a_moves)
{
	while (a_moves > 0)
	{
		ra(a, 1);
		a_moves--;
	}
	while (a_moves < 0)
	{
		rra(a, 1);
		a_moves++;
	}
}

static void	execute_b_moves(t_stack *b, int b_moves)
{
	while (b_moves > 0)
	{
		rb(b, 1);
		b_moves--;
	}
	while (b_moves < 0)
	{
		rrb(b, 1);
		b_moves++;
	}
}

void	execute_moves(t_stack *a, t_stack *b, t_cost cost)
{
	int	a_moves;
	int	b_moves;

	a_moves = cost.a_moves;
	b_moves = cost.b_moves;
	execute_simultaneous_moves(a, b, &a_moves, &b_moves);
	execute_a_moves(a, a_moves);
	execute_b_moves(b, b_moves);
	pa(a, b, 1);
}
