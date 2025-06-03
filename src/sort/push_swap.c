/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 19:29:26 by mirokugo          #+#    #+#             */
/*   Updated: 2025/06/03 20:00:00 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

void	push_swap(t_stack *stack_a, t_stack *stack_b)
{
	int	size;

	size = stack_a->top + 1;
	if (is_sorted(stack_a))
		return ;
	if (size == 2)
		sort_two(stack_a);
	else if (size == 3)
		sort_three(stack_a);
	else if (size == 4)
		sort_four(stack_a, stack_b);
	else if (size == 5)
		sort_five(stack_a, stack_b);
	else if (size <= 100)
	{
		optimized_sort(stack_a, stack_b);
	}
	else if (size <= 500)
	{
		simple_dp_sort(stack_a, stack_b);
	}
	else
	{
		radix_sort(stack_a, stack_b);
	}
}
