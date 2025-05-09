/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:51:39 by mirokugo          #+#    #+#             */
/*   Updated: 2025/03/12 15:51:39 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

// クイックソートのパーティション関数
int partition(int *arr, int low, int high)
{
    int pivot = arr[high];  // 最後の要素をピボットとして選択
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        // 現在の要素がピボット以下の場合
        if (arr[j] <= pivot)
        {
            i++;
            // arr[i] と arr[j] を交換
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    // ピボットを正しい位置に配置
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1;
}

// クイックソートの再帰関数
void quick_sort(int *arr, int low, int high)
{
    if (low < high)
    {
        // パーティションのインデックスを取得
        int pi = partition(arr, low, high);

        // 分割統治法で左右のサブ配列をソート
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

