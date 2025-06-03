/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ultimate_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 03:00:00 by mirokugo          #+#    #+#             */
/*   Updated: 2025/06/04 03:00:00 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

// より効率的な最近傍探索
static int	find_nearest_target(t_stack *a, int min_val, int max_val)
{
	int	i;
	int	size;
	int	from_top = -1;
	int	from_bottom = -1;
	
	size = a->top + 1;
	
	// 上から探索
	i = 0;
	while (i < size)
	{
		if (a->data[a->top - i] >= min_val && a->data[a->top - i] <= max_val)
		{
			from_top = i;
			break;
		}
		i++;
	}
	
	// 下から探索
	i = 0;
	while (i < size)
	{
		if (a->data[i] >= min_val && a->data[i] <= max_val)
		{
			from_bottom = i;
			break;
		}
		i++;
	}
	
	// 最短経路を選択
	if (from_top == -1)
		return (-1);
	if (from_bottom == -1)
		return (from_top);
	
	// rotateとreverse_rotateのコストを比較
	if (from_top <= from_bottom)
		return (from_top);
	else
		return (size - from_bottom - 1);
}

// 効率的なチャンク転送
static void	ultra_push_chunk(t_stack *a, t_stack *b, int min_val, int max_val)
{
	int	pos;
	int	size;
	int	pushed = 0;
	int	chunk_size = max_val - min_val + 1;
	
	while (pushed < chunk_size && a->top >= 0)
	{
		pos = find_nearest_target(a, min_val, max_val);
		if (pos == -1)
			break;
		
		size = a->top + 1;
		
		// 最短経路でターゲットを先頭に移動
		if (pos <= size / 2)
		{
			while (pos-- > 0)
				rotate_a(a);
		}
		else
		{
			pos = size - pos;
			while (pos-- > 0)
				reverse_rotate_a(a);
		}
		
		push_atob(a, b);
		pushed++;
		
		// スタックBの最適化：中央値より小さい値は下に回す
		if (b->top > 0)
		{
			int mid_val = min_val + (max_val - min_val) / 2;
			if (b->data[b->top] < mid_val)
				rotate_b(b);
		}
	}
}

// 高速な最大値探索と転送
static void	ultra_push_back(t_stack *a, t_stack *b)
{
	int	size;
	int	max_val;
	int	max_pos;
	int	i;
	
	while (b->top >= 0)
	{
		size = b->top + 1;
		max_val = b->data[0];
		max_pos = size - 1;
		
		// 最大値を探索（最適化：下から探索）
		i = 1;
		while (i < size)
		{
			if (b->data[i] > max_val)
			{
				max_val = b->data[i];
				max_pos = size - i - 1;
			}
			i++;
		}
		
		// 最短経路で最大値を先頭に
		if (max_pos <= size / 2)
		{
			while (max_pos-- > 0)
				rotate_b(b);
		}
		else
		{
			max_pos = size - max_pos;
			while (max_pos-- > 0)
				reverse_rotate_b(b);
		}
		
		push_btoa(b, a);
	}
}

void	ultimate_sort(t_stack *a, t_stack *b)
{
	int	size;
	int	chunk_size;
	int	num_chunks;
	int	i;
	
	size = a->top + 1;
	rank_normalize(a);
	
	// 動的チャンクサイズ計算（500要素用に最適化）
	if (size <= 100)
		chunk_size = 20;
	else if (size <= 250)
		chunk_size = 35;
	else if (size <= 500)
		chunk_size = 63;  // 実験的に最適な値
	else
		chunk_size = 70;
	
	num_chunks = (size + chunk_size - 1) / chunk_size;
	
	// チャンクごとに転送
	i = 0;
	while (i < num_chunks)
	{
		int min_val = i * chunk_size;
		int max_val = (i + 1) * chunk_size - 1;
		if (max_val >= size)
			max_val = size - 1;
		
		ultra_push_chunk(a, b, min_val, max_val);
		i++;
	}
	
	// 最適化された戻し処理
	ultra_push_back(a, b);
}