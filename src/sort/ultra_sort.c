/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ultra_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 22:00:00 by mirokugo          #+#    #+#             */
/*   Updated: 2025/06/03 22:00:00 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

static int	get_max_bits_ultra(int max_val)
{
	int	bits;

	bits = 0;
	while ((max_val >> bits) != 0)
		bits++;
	return (bits);
}


void	ultra_sort(t_stack *stack_a, t_stack *stack_b)
{
	int	max_bits;
	int	size;
	int	i;
	int	j;
	int	moved_to_b;

	size = stack_a->top + 1;
	rank_normalize(stack_a);
	max_bits = get_max_bits_ultra(size - 1);
	
	i = 0;
	while (i < max_bits)
	{
		j = 0;
		moved_to_b = 0;
		while (j < size)
		{
			if (((stack_a->data[stack_a->top] >> i) & 1) == 0)
			{
				push_atob(stack_a, stack_b);
				moved_to_b++;
			}
			else
				rotate_a(stack_a);
			j++;
		}
		
		// 効率的にBからAに戻す
		while (moved_to_b > 0)
		{
			push_btoa(stack_b, stack_a);
			moved_to_b--;
		}
		i++;
	}
}