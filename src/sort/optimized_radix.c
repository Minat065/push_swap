/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimized_radix.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 01:00:00 by mirokugo          #+#    #+#             */
/*   Updated: 2025/06/04 01:00:00 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

// 最適化1: 不要なrotateを削減
static void	smart_bit_process(t_stack *a, t_stack *b, int bit, int size)
{
	int	processed = 0;
	int	zeros_found = 0;
	int	ones_found = 0;
	
	// 事前カウント
	int i = 0;
	while (i < size)
	{
		if (((a->data[a->top - i] >> bit) & 1) == 0)
			zeros_found++;
		else
			ones_found++;
		i++;
	}
	
	// zeros_foundが少ない場合は逆処理（1をpush）
	if (zeros_found > size * 0.7)
	{
		// 通常処理：0をpush
		while (processed < size)
		{
			if (((a->data[a->top] >> bit) & 1) == 0)
				push_atob(a, b);
			else
				rotate_a(a);
			processed++;
		}
	}
	else if (zeros_found < size * 0.3)
	{
		// 逆処理：1をpush
		while (processed < size)
		{
			if (((a->data[a->top] >> bit) & 1) == 1)
				push_atob(a, b);
			else
				rotate_a(a);
			processed++;
		}
	}
	else
	{
		// 標準処理
		while (processed < size)
		{
			if (((a->data[a->top] >> bit) & 1) == 0)
				push_atob(a, b);
			else
				rotate_a(a);
			processed++;
		}
	}
}

// 最適化2: 8ビット制限での処理
static void	compress_to_8bit(t_stack *stack)
{
	int	size = stack->top + 1;
	int	i;
	
	// 500要素を0-255にマッピング
	for (i = 0; i <= stack->top; i++)
	{
		stack->data[i] = (stack->data[i] * 255) / (size - 1);
	}
}

// 最適化3: 早期終了
static int	is_bit_sorted(t_stack *a, int bit)
{
	int	i;
	int	prev_bit = (a->data[a->top] >> bit) & 1;
	
	for (i = 1; i <= a->top; i++)
	{
		int curr_bit = (a->data[a->top - i] >> bit) & 1;
		if (prev_bit > curr_bit)
			return (0);
		prev_bit = curr_bit;
	}
	return (1);
}

void	optimized_radix(t_stack *stack_a, t_stack *stack_b)
{
	int	size;
	int	max_bits;
	int	bit;

	size = stack_a->top + 1;
	if (size <= 1)
		return;

	rank_normalize(stack_a);
	
	// 最適化: 8ビットに圧縮
	compress_to_8bit(stack_a);
	max_bits = 8;
	
	bit = 0;
	while (bit < max_bits)
	{
		// 早期終了チェック
		if (is_bit_sorted(stack_a, bit))
		{
			bit++;
			continue;
		}
		
		smart_bit_process(stack_a, stack_b, bit, size);
		
		// Bの全要素をAに戻す
		while (stack_b->top >= 0)
			push_btoa(stack_b, stack_a);
		
		bit++;
	}
}