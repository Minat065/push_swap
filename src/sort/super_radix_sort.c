/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   super_radix_sort.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 23:00:00 by mirokugo          #+#    #+#             */
/*   Updated: 2025/06/03 23:00:00 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

static int	get_max_bits_super(int max_val)
{
	int	bits;

	bits = 0;
	while ((max_val >> bits) != 0)
		bits++;
	return (bits);
}

// 4ビットずつ処理する高速radix sort
static void	radix_sort_4bit(t_stack *stack_a, t_stack *stack_b, int start_bit)
{
	int	size;
	int	i;
	int	bit_mask;

	size = stack_a->top + 1;
	bit_mask = 0xF << start_bit; // 4ビットマスク

	// 4ビットの値に基づいて分割（0-15の範囲）
	for (int value = 0; value < 16; value++)
	{
		i = 0;
		while (i < size)
		{
			int current_4bit = (stack_a->data[stack_a->top] & bit_mask) >> start_bit;
			if (current_4bit == value)
			{
				push_atob(stack_a, stack_b);
			}
			else
			{
				rotate_a(stack_a);
			}
			i++;
		}
		
		// この値の要素をすべて戻す
		while (stack_b->top >= 0)
			push_btoa(stack_b, stack_a);
	}
}

void	super_radix_sort(t_stack *stack_a, t_stack *stack_b)
{
	int	max_bits;
	int	size;
	int	bit;

	size = stack_a->top + 1;
	if (size <= 1)
		return;

	rank_normalize(stack_a);
	max_bits = get_max_bits_super(size - 1);
	
	// 4ビットずつ処理
	for (bit = 0; bit < max_bits; bit += 4)
	{
		if (bit + 4 <= max_bits)
			radix_sort_4bit(stack_a, stack_b, bit);
		else
		{
			// 残りのビットを処理
			int remaining_bits = max_bits - bit;
			int i, j;
			for (i = 0; i < remaining_bits; i++)
			{
				j = 0;
				while (j < size)
				{
					if (((stack_a->data[stack_a->top] >> (bit + i)) & 1) == 0)
						push_atob(stack_a, stack_b);
					else
						rotate_a(stack_a);
					j++;
				}
				while (stack_b->top >= 0)
					push_btoa(stack_b, stack_a);
			}
		}
	}
}