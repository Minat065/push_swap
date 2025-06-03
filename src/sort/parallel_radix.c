/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parallel_radix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 02:00:00 by mirokugo          #+#    #+#             */
/*   Updated: 2025/06/04 02:00:00 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

// 同時rotate操作
static void	rotate_both(t_stack *a, t_stack *b)
{
	write(1, "rr\n", 3);
	// rotate a
	if (a->top > 0)
	{
		int temp = a->data[a->top];
		int i = a->top;
		while (i > 0)
		{
			a->data[i] = a->data[i - 1];
			i--;
		}
		a->data[0] = temp;
	}
	// rotate b
	if (b->top > 0)
	{
		int temp = b->data[b->top];
		int i = b->top;
		while (i > 0)
		{
			b->data[i] = b->data[i - 1];
			i--;
		}
		b->data[0] = temp;
	}
}


// 並列処理を活用したビット処理
static void	parallel_bit_process(t_stack *a, t_stack *b, int bit, int size)
{
	int	i = 0;
	int	pushed = 0;
	
	// フェーズ1: AからBへの分配（通常処理）
	while (i < size)
	{
		if (((a->data[a->top] >> bit) & 1) == 0)
		{
			push_atob(a, b);
			pushed++;
		}
		else
			rotate_a(a);
		i++;
	}
	
	// フェーズ2: 並列処理でBからAへ戻す
	// Bのサイズに応じて最適な戦略を選択
	if (pushed > 0 && pushed < size)
	{
		// 両方のスタックに要素がある場合、同時操作を活用
		int	a_needs_rotate = size - pushed;
		int	b_size = pushed;
		
		// 同時rotateが可能な回数を計算
		int	min_rotates = (a_needs_rotate < b_size) ? a_needs_rotate : b_size;
		
		// 同時rotate実行
		i = 0;
		while (i < min_rotates && b->top >= 0)
		{
			// Bの先頭要素を確認
			if (((b->data[b->top] >> bit) & 1) == 0)
			{
				push_btoa(b, a);
				// Aも回転が必要なら同時実行
				if (a_needs_rotate > 0)
				{
					rotate_a(a);
					a_needs_rotate--;
				}
			}
			else
			{
				// 両方を同時にrotate
				rotate_both(a, b);
				a_needs_rotate--;
			}
			i++;
		}
		
		// 残りの要素を処理
		while (b->top >= 0)
			push_btoa(b, a);
	}
	else
	{
		// 全てBに移動した場合は単純に戻す
		while (b->top >= 0)
			push_btoa(b, a);
	}
}

void	parallel_radix(t_stack *stack_a, t_stack *stack_b)
{
	int	size;
	int	max_bits;
	int	bit;

	size = stack_a->top + 1;
	if (size <= 1)
		return;

	rank_normalize(stack_a);
	
	// 最大値はsize-1（インデックス値なので）
	int max_val = size - 1;
	max_bits = 0;
	while ((max_val >> max_bits) != 0)
		max_bits++;
	
	bit = 0;
	while (bit < max_bits)
	{
		parallel_bit_process(stack_a, stack_b, bit, size);
		bit++;
	}
}