/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_sorted.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:50:58 by mirokugo          #+#    #+#             */
/*   Updated: 2025/03/11 11:50:58 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

int is_sorted(t_stack *stack)
{
    int i;
    
    if (stack->top <= 0)
        return 1;
    
    // Check if stack is sorted: smallest at top (stack->data[top]), largest at bottom
    // Each element should be <= next element down
    for (i = stack->top; i > 0; i--)
    {
        if (stack->data[i] > stack->data[i-1])
            return 0;
    }
    return 1;
}