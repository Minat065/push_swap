/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rank_normalize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:00:03 by mirokugo          #+#    #+#             */
/*   Updated: 2025/03/11 12:00:03 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

void rank_normalize(t_stack *stack) 
{
    int size = stack->top + 1;
    int *sorted_copy;
    int *ranks;
    int i, j;
    
    sorted_copy = malloc(sizeof(int) * size);
    ranks = malloc(sizeof(int) * size);
    
    if (!sorted_copy || !ranks) {
        if (sorted_copy) free(sorted_copy);
        if (ranks) free(ranks);
        return;
    }
    
    // データのコピー
    for (i = 0; i < size; i++)
        sorted_copy[i] = stack->data[i];
    
    // 昇順ソート
    quick_sort(sorted_copy, 0, size - 1);
    
    // 各要素のランクを計算
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            if (stack->data[i] == sorted_copy[j]) {
                ranks[i] = j;
                // 重複値がある場合は最初のものだけを使用
                break;
            }
        }
    }
    
    // オリジナルのスタックデータをランク値に置き換え
    for (i = 0; i < size; i++)
        stack->data[i] = ranks[i];
    
    free(sorted_copy);
    free(ranks);
}