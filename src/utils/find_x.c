/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_x.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:46:36 by mirokugo          #+#    #+#             */
/*   Updated: 2025/03/12 15:46:36 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

int find_max(t_stack *stack)
{
    int max = stack->data[0];
    
    for (int i = 1; i <= stack->top; i++)
    {
        if (stack->data[i] > max)
            max = stack->data[i];
    }
    
    return max;
}

int find_min(t_stack *stack)
{
    int min = stack->data[0];
    
    for (int i = 1; i <= stack->top; i++)
    {
        if (stack->data[i] < min)
            min = stack->data[i];
    }
    
    return min;
}

int find_min_position(t_stack *stack)
{
    int min_value = stack->data[0];
    int min_pos = 0;
    
    for (int i = 1; i <= stack->top; i++)
    {
        if (stack->data[i] < min_value)
        {
            min_value = stack->data[i];
            min_pos = i;
        }
    }
    
    return min_pos;
}