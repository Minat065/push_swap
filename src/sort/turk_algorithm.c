/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turk_algorithm.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 23:30:00 by mirokugo          #+#    #+#             */
/*   Updated: 2025/06/03 23:30:00 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

static void	push_to_b_optimized(t_stack *a, t_stack *b)
{
	int	chunk_size;
	int	size;
	int	min_chunk;
	int	max_chunk;
	int	chunk;

	size = a->top + 1;
	chunk_size = size / 7; // 500要素なら約70ずつ
	if (chunk_size < 1)
		chunk_size = 1;
	
	chunk = 0;
	while (a->top > 2)
	{
		min_chunk = chunk * chunk_size;
		max_chunk = (chunk + 1) * chunk_size - 1;
		if (max_chunk >= size)
			max_chunk = size - 1;
		
		// 現在のチャンクに属する要素をBに移動
		int moved = 0;
		int rotations = 0;
		while (moved < chunk_size && a->top > 2 && rotations < size)
		{
			if (a->data[a->top] >= min_chunk && a->data[a->top] <= max_chunk)
			{
				push_atob(a, b);
				moved++;
				rotations = 0;
			}
			else
			{
				rotate_a(a);
				rotations++;
			}
		}
		chunk++;
	}
}

static void	sort_three_elements(t_stack *a)
{
	int	first = a->data[a->top];
	int	second = a->data[a->top - 1];
	int	third = a->data[a->top - 2];

	if (first > second && second < third && first < third)
		swap_a(a);
	else if (first > second && second > third)
	{
		swap_a(a);
		reverse_rotate_a(a);
	}
	else if (first > second && second < third && first > third)
		rotate_a(a);
	else if (first < second && second > third && first < third)
	{
		swap_a(a);
		rotate_a(a);
	}
	else if (first < second && second > third && first > third)
		reverse_rotate_a(a);
}


static void	push_back_optimized(t_stack *a, t_stack *b)
{
	int	max_val;
	int	max_pos;
	int	i;

	while (b->top >= 0)
	{
		// Bスタックの最大値を見つける
		max_val = b->data[0];
		max_pos = 0;
		i = 1;
		while (i <= b->top)
		{
			if (b->data[i] > max_val)
			{
				max_val = b->data[i];
				max_pos = i;
			}
			i++;
		}
		
		// 最大値をトップに回転
		while (max_pos > 0)
		{
			if (max_pos <= (b->top + 1) / 2)
			{
				rotate_b(b);
				max_pos--;
			}
			else
			{
				reverse_rotate_b(b);
				max_pos++;
				if (max_pos > b->top)
					max_pos = 0;
			}
		}
		
		push_btoa(b, a);
	}
}

static void	final_sort_a(t_stack *a)
{
	int	min_pos = 0;
	int	min_val = a->data[0];
	int	i;
	int	size;
	
	size = a->top + 1;
	
	// 最小値の位置を見つける
	i = 1;
	while (i <= a->top)
	{
		if (a->data[i] < min_val)
		{
			min_val = a->data[i];
			min_pos = i;
		}
		i++;
	}
	
	// 最小値をトップに移動
	min_pos = a->top - min_pos;
	while (min_pos > 0)
	{
		if (min_pos <= size / 2)
		{
			rotate_a(a);
			min_pos--;
		}
		else
		{
			reverse_rotate_a(a);
			min_pos++;
			if (min_pos >= size)
				min_pos = 0;
		}
	}
}

void	turk_algorithm(t_stack *stack_a, t_stack *stack_b)
{
	if (stack_a->top < 1)
		return;
	
	rank_normalize(stack_a);
	
	// フェーズ1: 3つを除いてBに移動
	push_to_b_optimized(stack_a, stack_b);
	
	// フェーズ2: 残り3つをソート
	sort_three_elements(stack_a);
	
	// フェーズ3: Bから最適順序でAに戻す
	push_back_optimized(stack_a, stack_b);
	
	// フェーズ4: Aを最終的にソート
	final_sort_a(stack_a);
}