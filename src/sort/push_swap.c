/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 19:29:26 by mirokugo          #+#    #+#             */
/*   Updated: 2025/02/26 19:34:14 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

void    push_swap(t_stack *stack_a, t_stack *stack_b)
{
    int i;

    i = 0;
    while (sort_checker(stack_a, stack_b))
    {
        if (stack_a->data[stack_a->top] > stack_a->data[stack_a->top - 1])
        {
            swap_a(stack_a);
            i++;
        }

        else
        {
            if (stack_b->top == -1)
                push_atob(stack_a, stack_b);
            else if (stack_b->data[stack_b->top] < stack_a->data[stack_a->top])
                push_atob(stack_a, stack_b);
            else
                rotate_a(stack_a);
        }
    }
}

int sort_checker(t_stack *stack_a, t_stack *stack_b)
{
    int i;

    i = 0;
    while (i < stack_a->top)
    {
        if (stack_a->data[i] > stack_a->data[i + 1])
            return (1);
        i++;
    }
    
    if (stack_b->top != -1)
        return (1);

    

    ft_printf("OK\n");
    return (0);
}



