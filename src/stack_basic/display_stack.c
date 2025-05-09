/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_stack.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:57:57 by mirokugo          #+#    #+#             */
/*   Updated: 2025/03/12 17:12:00 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../../includes/push_swap.h"

void display_stack(t_stack *a, t_stack *b)
{
    int i;

    ft_printf("stack contents : \n");
    
    // 配列インデックス順（ボトムからトップ）に表示
    for (i = 0; i <= a->top; i++)
    {
        ft_printf("%d |  %d | ", i, a->data[i]);
        
        if (i <= b->top)
            ft_printf(" %d", b->data[i]);
        
        ft_printf("\n");
    }
    
    ft_printf("i | a | b\n");
}
