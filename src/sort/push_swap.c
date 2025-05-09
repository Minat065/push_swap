/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 19:29:26 by mirokugo          #+#    #+#             */
/*   Updated: 2025/03/12 17:05:29 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

void push_swap(t_stack *stack_a, t_stack *stack_b)
{
    int size = stack_a->top + 1;
    int *original_values;
    int i;
    
    // すでにソート済みなら何もしない
    if (is_sorted(stack_a))
        return;
    
    // 小規模データ用の特殊処理
    if (size == 2)
    {
        if (stack_a->data[stack_a->top] > stack_a->data[stack_a->top - 1])
            swap_a(stack_a);
    }
    else if (size == 3)
        sort_three(stack_a);
    else if (size <= 5)
        sort_four_five(stack_a, stack_b);
    else
    {
        // 元の値を保存
        original_values = (int *)malloc(sizeof(int) * size);
        if (!original_values)
            return;
    
        // 元の値をコピー
        for (i = 0; i <= stack_a->top; i++)
            original_values[i] = stack_a->data[i];
    
        // ランク正規化を実行
        rank_normalize(stack_a);
    
        // ラジックスソートでランク値をソート
        radix_sort(stack_a, stack_b);
    
        // 元の値を対応するランクに基づいて復元
        restore_original_values(stack_a, original_values);
    
        // メモリ解放
        free(original_values);
    }
}

// 元の値を復元する関数
void restore_original_values(t_stack *stack, int *original_values)
{
    int size = stack->top + 1;
    int *temp = (int *)malloc(sizeof(int) * size);
    int i;
    
    if (!temp)
        return;
    
    // 現在のスタックの内容をコピー
    for (i = 0; i < size; i++)
        temp[i] = stack->data[i];
    
    // ランク値に基づいて元の値を復元
    for (i = 0; i < size; i++) {
        if (temp[i] >= 0 && temp[i] < size)
            stack->data[i] = original_values[temp[i]];
    }
    
    free(temp);
}