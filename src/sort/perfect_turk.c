/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perfect_turk.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 00:30:00 by mirokugo          #+#    #+#             */
/*   Updated: 2025/06/04 00:30:00 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

// Bスタックに単純に全要素をpush（3つ残す）
static void	push_all_to_b(t_stack *a, t_stack *b)
{
	while (a->top > 2)
		push_atob(a, b);
}

// Aの3要素をソート
static void	sort_three_turk(t_stack *a)
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

// Bから最大値を見つけてAに戻す
static void	push_back_max(t_stack *a, t_stack *b)
{
	int	max_val = b->data[0];
	int	max_index = 0;
	int	size = b->top + 1;
	int	i;

	// 最大値の位置を特定
	i = 1;
	while (i < size)
	{
		if (b->data[i] > max_val)
		{
			max_val = b->data[i];
			max_index = i;
		}
		i++;
	}

	// 最大値をトップに移動
	if (max_index <= size / 2)
	{
		while (max_index > 0)
		{
			rotate_b(b);
			max_index--;
		}
	}
	else
	{
		while (max_index < size)
		{
			reverse_rotate_b(b);
			max_index++;
			if (max_index == size)
				max_index = 0;
		}
	}

	push_btoa(b, a);
}

// 最小値をスタックのボトムに移動
static void	rotate_min_to_top(t_stack *a)
{
	int	min_val = a->data[0];
	int	min_index = 0;
	int	size = a->top + 1;
	int	i;

	// 最小値の位置を特定
	i = 1;
	while (i < size)
	{
		if (a->data[i] < min_val)
		{
			min_val = a->data[i];
			min_index = i;
		}
		i++;
	}

	// 最小値をトップに移動
	if (min_index <= size / 2)
	{
		while (min_index > 0)
		{
			rotate_a(a);
			min_index--;
		}
	}
	else
	{
		while (min_index < size)
		{
			reverse_rotate_a(a);
			min_index++;
			if (min_index == size)
				min_index = 0;
		}
	}
}

void	perfect_turk(t_stack *stack_a, t_stack *stack_b)
{
	if (stack_a->top < 1)
		return;

	rank_normalize(stack_a);

	// フェーズ1: 3つを残してBに移動
	push_all_to_b(stack_a, stack_b);

	// フェーズ2: 残り3つをソート
	sort_three_turk(stack_a);

	// フェーズ3: Bから降順でAに戻す
	while (stack_b->top >= 0)
		push_back_max(stack_a, stack_b);

	// フェーズ4: 最小値をトップに移動（昇順完成）
	rotate_min_to_top(stack_a);
}