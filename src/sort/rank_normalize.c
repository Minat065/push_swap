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

// インデックス配列を値でソートするためのヘルパー
static int *g_values; // グローバル参照用

static void swap_indices(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

static int partition_indices(int *indices, int low, int high)
{
    int pivot = g_values[indices[high]];
    int i = low - 1;
    int j;

    for (j = low; j < high; j++) {
        if (g_values[indices[j]] <= pivot) {
            i++;
            swap_indices(&indices[i], &indices[j]);
        }
    }
    swap_indices(&indices[i + 1], &indices[high]);
    return i + 1;
}

static void quick_sort_indices(int *indices, int low, int high)
{
    if (low < high) {
        int pi = partition_indices(indices, low, high);
        quick_sort_indices(indices, low, pi - 1);
        quick_sort_indices(indices, pi + 1, high);
    }
}

void rank_normalize(t_stack *stack) 
{
    int size = stack->top + 1;
    int *indices;
    int *ranks;
    int i;
    
    indices = malloc(sizeof(int) * size);
    ranks = malloc(sizeof(int) * size);
    
    if (!indices || !ranks) {
        if (indices) free(indices);
        if (ranks) free(ranks);
        return;
    }
    
    // インデックス配列を初期化
    for (i = 0; i < size; i++)
        indices[i] = i;
    
    // グローバル参照を設定
    g_values = stack->data;
    
    // インデックスを値でソート (O(n log n))
    quick_sort_indices(indices, 0, size - 1);
    
    // ランクを割り当て (O(n))
    for (i = 0; i < size; i++)
        ranks[indices[i]] = i;
    
    // オリジナルのスタックデータをランク値に置き換え
    for (i = 0; i < size; i++)
        stack->data[i] = ranks[i];
    
    free(indices);
    free(ranks);
}