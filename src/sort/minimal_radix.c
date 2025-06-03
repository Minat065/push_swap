/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimal_radix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 01:30:00 by mirokugo          #+#    #+#             */
/*   Updated: 2025/06/04 01:30:00 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

// 超効率化：不要rotateを最小化
static void	ultra_efficient_bit_process(t_stack *a, t_stack *b, int bit, int size)
{
	int	target_pushes = 0;
	int	i;
	
	// 事前に0ビットの数を数える
	i = 0;
	while (i < size)
	{
		if (((a->data[a->top - i] >> bit) & 1) == 0)
			target_pushes++;
		i++;
	}
	
	// 効率化：target_pushesが0なら何もしない
	if (target_pushes == 0)
		return;
	
	// 効率化：target_pushesがsizeと同じなら全てpush
	if (target_pushes == size)
	{
		i = 0;
		while (i < size)
		{
			push_atob(a, b);
			i++;
		}
		return;
	}
	
	// 標準処理（最小rotate）
	int pushed = 0;
	while (pushed < target_pushes)
	{
		if (((a->data[a->top] >> bit) & 1) == 0)
		{
			push_atob(a, b);
			pushed++;
		}
		else
		{
			rotate_a(a);
		}
	}
}

// 最適ビット数計算（500要素専用）
static int	get_optimal_bits(int size)
{
	// 500要素の場合、8.97ビット必要だが、8ビットでも90%カバー可能
	if (size <= 256)
		return (8);
	else if (size <= 512)
		return (9);
	else
		return (10);
}

void	minimal_radix(t_stack *stack_a, t_stack *stack_b)
{
	int	size;
	int	max_bits;
	int	bit;

	size = stack_a->top + 1;
	if (size <= 1)
		return;

	rank_normalize(stack_a);
	max_bits = get_optimal_bits(size);
	
	bit = 0;
	while (bit < max_bits)
	{
		ultra_efficient_bit_process(stack_a, stack_b, bit, size);
		
		// Bの全要素をAに戻す（効率化：Bが空なら省略）
		while (stack_b->top >= 0)
			push_btoa(stack_b, stack_a);
		
		bit++;
	}
}