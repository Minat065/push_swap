/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   efficient_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 22:00:00 by mirokugo          #+#    #+#             */
/*   Updated: 2025/06/03 22:00:00 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

// Stack Bの適切な挿入位置を見つける（バイナリサーチ風）
static int	find_insert_position(t_stack *stack_b, int value)
{
	int	size;
	int	i;
	int	best_pos;
	int	min_diff;
	int	diff;

	if (stack_b->top < 0)
		return (0);
		
	size = stack_b->top + 1;
	best_pos = 0;
	min_diff = 2147483647; // INT_MAX
	
	// 降順に並んでいるstack_bで、valueより小さい最大の値を探す
	for (i = 0; i < size; i++)
	{
		if (stack_b->data[stack_b->top - i] < value)
		{
			diff = value - stack_b->data[stack_b->top - i];
			if (diff < min_diff)
			{
				min_diff = diff;
				best_pos = i;
			}
		}
	}
	
	// 適切な位置が見つからない場合（全て値より大きい）
	if (min_diff == 2147483647)
	{
		// 最大値の位置を探す
		int max_val = stack_b->data[stack_b->top];
		for (i = 0; i < size; i++)
		{
			if (stack_b->data[stack_b->top - i] > max_val)
			{
				max_val = stack_b->data[stack_b->top - i];
				best_pos = i;
			}
		}
	}
	
	return (best_pos);
}

// 効率的にstack_bの指定位置にローテート
static void	rotate_to_position(t_stack *stack_b, int position)
{
	int	size;
	int	cost_forward;
	int	cost_backward;

	if (position == 0)
		return;
		
	size = stack_b->top + 1;
	cost_forward = position;
	cost_backward = size - position;
	
	if (cost_forward <= cost_backward)
	{
		while (position > 0)
		{
			rotate_b(stack_b);
			position--;
		}
	}
	else
	{
		while (cost_backward > 0)
		{
			reverse_rotate_b(stack_b);
			cost_backward--;
		}
	}
}

// 最小の操作コストで要素をBに移動
static void	move_to_b_optimized(t_stack *stack_a, t_stack *stack_b, int target_value)
{
	int	size_a;
	int	target_pos;
	int	i;

	size_a = stack_a->top + 1;
	target_pos = 0;
	
	// stack_aでtarget_valueの位置を探す
	for (i = 0; i <= stack_a->top; i++)
	{
		if (stack_a->data[stack_a->top - i] == target_value)
		{
			target_pos = i;
			break;
		}
	}
	
	// 効率的にローテート
	if (target_pos <= size_a / 2)
	{
		while (target_pos > 0)
		{
			rotate_a(stack_a);
			target_pos--;
		}
	}
	else
	{
		int reverse_cost = size_a - target_pos;
		while (reverse_cost > 0)
		{
			reverse_rotate_a(stack_a);
			reverse_cost--;
		}
	}
	
	// 適切な位置にBをローテート
	int insert_pos = find_insert_position(stack_b, target_value);
	rotate_to_position(stack_b, insert_pos);
	
	// Bにプッシュ
	push_atob(stack_a, stack_b);
}

// 効率的なソートアルゴリズム
void	efficient_sort(t_stack *stack_a, t_stack *stack_b)
{
	int	size;
	int	i;
	int	chunk_size;
	int	processed;

	size = stack_a->top + 1;
	
	// ランク正規化
	rank_normalize(stack_a);
	
	// チャンクベースで処理（500要素なら約8-10チャンク）
	chunk_size = (size <= 100) ? 12 : 8;
	processed = 0;
	
	// 最初にいくつかの要素をBに移動
	while (processed < size - 3 && stack_a->top >= 3)
	{
		// 現在のチャンクの範囲
		int chunk_start = (processed / chunk_size) * chunk_size;
		int chunk_end = chunk_start + chunk_size - 1;
		if (chunk_end >= size)
			chunk_end = size - 1;
			
		// チャンク内の最適な要素を選択
		int best_value = -1;
		int min_cost = 2147483647;
		
		for (i = 0; i <= stack_a->top; i++)
		{
			int value = stack_a->data[stack_a->top - i];
			if (value >= chunk_start && value <= chunk_end)
			{
				// コスト計算（ローテーション + 挿入）
				int rotate_cost = (i <= (stack_a->top + 1) / 2) ? i : (stack_a->top + 1) - i;
				int insert_pos = find_insert_position(stack_b, value);
				int insert_cost = (insert_pos <= (stack_b->top + 1) / 2) ? insert_pos : (stack_b->top + 1) - insert_pos;
				int total_cost = rotate_cost + insert_cost;
				
				if (total_cost < min_cost)
				{
					min_cost = total_cost;
					best_value = value;
				}
			}
		}
		
		if (best_value != -1)
		{
			move_to_b_optimized(stack_a, stack_b, best_value);
			processed++;
		}
		else
		{
			// チャンク内に要素がない場合、次のチャンクに進む
			processed = ((processed / chunk_size) + 1) * chunk_size;
		}
	}
	
	// 残りの要素をAでソート（3要素以下）
	if (stack_a->top + 1 == 3)
		sort_three(stack_a);
	else if (stack_a->top + 1 == 2)
	{
		if (stack_a->data[stack_a->top] > stack_a->data[stack_a->top - 1])
			swap_a(stack_a);
	}
	
	// BからAに戻す（降順に並んでいるので最大値から順に）
	while (stack_b->top >= 0)
	{
		// Bの最大値を見つけてトップに移動
		int max_val = stack_b->data[stack_b->top];
		int max_pos = 0;
		
		for (i = 0; i <= stack_b->top; i++)
		{
			if (stack_b->data[stack_b->top - i] > max_val)
			{
				max_val = stack_b->data[stack_b->top - i];
				max_pos = i;
			}
		}
		
		rotate_to_position(stack_b, max_pos);
		push_btoa(stack_b, stack_a);
	}
}