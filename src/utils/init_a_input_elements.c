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
    
    stack_a->top = -1; // スタックを空に初期化
    
    // 引数を逆順にスタックに格納（トップが先頭要素になるように）
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