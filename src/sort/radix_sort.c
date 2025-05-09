/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:57:36 by mirokugo          #+#    #+#             */
/*   Updated: 2025/03/11 11:57:36 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

// void radix_sort(t_stack *stack_a, t_stack *stack_b)
// {
//     int max_bits = 0;
//     int size = stack_a->top + 1;
//     int i, j;
    
//     // 最大値はsize-1（インデックス値なので）
//     int max_val = size - 1;
    
//     // 必要なビット数を計算
//     while ((max_val >> max_bits) != 0)
//         max_bits++;
    
//     for (i = 0; i < max_bits; i++)
//     {
//         // 全要素を処理
//         for (j = 0; j < size; j++)
//         {
//             // トップの要素の現在のビットを確認
//             // もし0なら、スタックBへ移動
//             if (((stack_a->data[stack_a->top] >> i) & 1) == 0)
//                 push_atob(stack_a, stack_b);
//             else
//                 rotate_a(stack_a);
//         }
        
//         // スタックBの全要素をスタックAに戻す
//         while (stack_b->top >= 0)
//             push_btoa(stack_b, stack_a);
//     }
// }

void debug_stack(t_stack *stack, char *message)
{
    int i;
    
    ft_printf("%s - Stack contents:\n", message);
    for (i = 0; i <= stack->top; i++)
    {
        ft_printf("%d ", stack->data[i]);
    }
    ft_printf("\n");
}

void radix_sort(t_stack *stack_a, t_stack *stack_b)
{
    int max_bits = 0;
    int size = stack_a->top + 1;
    int i, j;
    
    // 最大値はsize-1（インデックス値なので）
    int max_val = size - 1;
    
    // 必要なビット数を計算
    while ((max_val >> max_bits) != 0)
        max_bits++;
    
    for (i = 0; i < max_bits; i++)
    {
        // 全要素を処理
        for (j = 0; j < size; j++)
        {
            // トップの要素の現在のビットを確認
            // もし0なら、スタックBへ移動
            if (((stack_a->data[stack_a->top] >> i) & 1) == 0)
                push_atob(stack_a, stack_b);
            else
                rotate_a(stack_a);
        }
        
        // スタックBの全要素をスタックAに戻す
        while (stack_b->top >= 0)
            push_btoa(stack_b, stack_a);
    }
}