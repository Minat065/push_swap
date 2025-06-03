/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enhanced_radix_sort.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 00:00:00 by mirokugo          #+#    #+#             */
/*   Updated: 2025/06/04 00:00:00 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

static int	get_max_bits_enhanced(int max_val)
{
	int	bits;

	bits = 0;
	while ((max_val >> bits) != 0)
		bits++;
	return (bits);
}

// 効率化：同じビットを持つ要素をまとめて処理
static void	process_bit_optimized(t_stack *a, t_stack *b, int bit, int size)
{
	int	processed;
	int	to_push;
	int	i;

	processed = 0;
	to_push = 0;
	
	// 最初にpushする要素数を数える
	i = 0;
	while (i < size)
	{
		if (((a->data[a->top - i] >> bit) & 1) == 0)
			to_push++;
		i++;
	}
	
	// 効率的にpushとrotateを実行
	while (processed < size)
	{
		if (((a->data[a->top] >> bit) & 1) == 0)
		{
			push_atob(a, b);
			to_push--;
		}
		else
		{
			rotate_a(a);
		}
		processed++;
		
		// 全ての0ビット要素を処理した場合は終了
		if (to_push == 0)
			break;
	}
}

void	enhanced_radix_sort(t_stack *stack_a, t_stack *stack_b)
{
	int	max_bits;
	int	size;
	int	bit;

	size = stack_a->top + 1;
	if (size <= 1)
		return;

	rank_normalize(stack_a);
	max_bits = get_max_bits_enhanced(size - 1);
	
	bit = 0;
	while (bit < max_bits)
	{
		process_bit_optimized(stack_a, stack_b, bit, size);
		
		// Bの全要素をAに戻す
		while (stack_b->top >= 0)
			push_btoa(stack_b, stack_a);
		
		bit++;
	}
}