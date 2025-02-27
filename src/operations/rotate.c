/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:36:04 by mirokugo          #+#    #+#             */
/*   Updated: 2025/02/26 18:09:17 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

void    rotate_a(t_stack *stack_a)
{
    int i;
    int tmp;

    if (stack_a->top < 1)
        return ;
    i = stack_a->top;
    tmp = stack_a->data[stack_a->top];
    while (i > 0)
    {
        stack_a->data[i] = stack_a->data[i - 1];
        i--;
    }
    stack_a->data[0] = tmp;
    ft_printf("ra\n");
}

void    rotate_b(t_stack *stack_b)
{
    int i;
    int tmp;

    if (stack_b->top < 1)
        return ;
    i = stack_b->top;
    tmp = stack_b->data[stack_b->top];
    while (i > 0)
    {
        stack_b->data[i] = stack_b->data[i - 1];
        i--;
    }
    stack_b->data[0] = tmp;
    ft_printf("rb\n");
}

void    reverse_rotate_a(t_stack *stack_a)
{
    int i;
    int tmp;

    if (stack_a->top < 1)
        return ;
    i = 0;
    tmp = stack_a->data[0];
    while (i < stack_a->top)
    {
        stack_a->data[i] = stack_a->data[i + 1];
        i++;
    }
    stack_a->data[stack_a->top] = tmp;
    ft_printf("rra\n");
}

void    reverse_rotate_b(t_stack *stack_b)
{
    int i;
    int tmp;

    if (stack_b->top < 1)
        return ;
    i = 0;
    tmp = stack_b->data[0];
    while (i < stack_b->top)
    {
        stack_b->data[i] = stack_b->data[i + 1];
        i++;
    }
    stack_b->data[stack_b->top] = tmp;
    ft_printf("rrb\n");
}