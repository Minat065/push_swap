/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_n.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:44:57 by mirokugo          #+#    #+#             */
/*   Updated: 2025/03/12 15:44:57 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

void sort_three(t_stack *stack_a)
{
    int a = stack_a->data[stack_a->top];
    int b = stack_a->data[stack_a->top - 1];
    int c = stack_a->data[stack_a->top - 2];
    
    if (a > b && b < c && a < c)
        swap_a(stack_a);
    else if (a > b && b > c)
    {
        swap_a(stack_a);
        reverse_rotate_a(stack_a);
    }
    else if (a > b && b < c && a > c)
        rotate_a(stack_a);
    else if (a < b && b > c && a < c)
    {
        swap_a(stack_a);
        rotate_a(stack_a);
    }
    else if (a < b && b > c && a > c)
        reverse_rotate_a(stack_a);
    // 1,2,3 パターンは既にソート済み
}

void sort_four_five(t_stack *stack_a, t_stack *stack_b)
{
    while (stack_a->top + 1 > 3)
    {
        int min_pos = find_min_position(stack_a);
        
        if (min_pos <= stack_a->top / 2)
        {
            while (min_pos < stack_a->top)
            {
                rotate_a(stack_a);
                min_pos++;
            }
        }
        else
        {
            while (min_pos < stack_a->top)
            {
                reverse_rotate_a(stack_a);
                min_pos = (min_pos == 0) ? stack_a->top : min_pos - 1;
            }
        }
        
        push_atob(stack_a, stack_b);
    }
    
    sort_three(stack_a);
    
    while (stack_b->top >= 0)
        push_btoa(stack_b, stack_a);
}