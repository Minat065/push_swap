/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_a_input_elements.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 18:54:09 by mirokugo          #+#    #+#             */
/*   Updated: 2025/03/12 15:59:50 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

// src/utils/init_a_input_elements.c
#include "../../includes/push_swap.h"

void init_a_input_elements(t_stack *stack_a, int argc, char **argv)
{
    int i;
    char **split_args;
    
    stack_a->top = -1; // スタックを空に初期化
    
    // 引数が1つだけの場合（空白区切りの数値列）
    if (argc == 2 && ft_strchr(argv[1], ' '))
    {
        split_args = ft_split(argv[1], ' ');
        if (!split_args)
        {
            write(2, "Error\n", 6);
            exit(EXIT_FAILURE);
        }
        
        // 分割された引数を逆順にスタックに格納（トップが先頭要素になるように）
        i = 0;
        while (split_args[i])
            i++;
            
        for (i = i - 1; i >= 0; i--)
        {
            validate_input(split_args[i], stack_a);
            if (!push(stack_a, ft_atoi(split_args[i])))
            {
                // メモリ解放
                int j = 0;
                while (split_args[j])
                {
                    if (j != i) // 現在処理中の要素は解放しない
                        free(split_args[j]);
                    j++;
                }
                free(split_args);
                write(2, "Error\n", 6);
                exit(EXIT_FAILURE);
            }
            free(split_args[i]);
        }
        free(split_args);
    }
    else
    {
        // 複数の引数の場合、引数を逆順にスタックに格納
        for (i = argc - 1; i > 0; i--)
        {
            validate_input(argv[i], stack_a);
            if (!push(stack_a, ft_atoi(argv[i])))
            {
                write(2, "Error\n", 6);
                exit(EXIT_FAILURE);
            }
        }
    }
}