/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_sort_method.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 20:00:48 by mirokugo          #+#    #+#             */
/*   Updated: 2025/02/23 20:35:29 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include	"../utils_libft/libft.h"
#include "../../includes/push_swap.h"

void    swap_a(t_stack *stack_a)
{
    int tmp;

    if (stack_a->top < 1)
        return ;
    tmp = stack_a->data[stack_a->top];
    stack_a->data[stack_a->top] = stack_a->data[stack_a->top - 1];
    stack_a->data[stack_a->top - 1] = tmp;
}

void    swap_b(t_stack *stack_b)
{
    int tmp;

    if (stack_b->top < 1)
        return ;
    tmp = stack_b->data[stack_b->top];
    stack_b->data[stack_b->top] = stack_b->data[stack_b->top - 1];
    stack_b->data[stack_b->top - 1] = tmp;
}
