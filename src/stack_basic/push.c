/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:55:16 by mirokugo          #+#    #+#             */
/*   Updated: 2025/03/12 16:01:00 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// src/stack_basic/push.c
#include "../../includes/push_swap.h"

int push(t_stack *s, int n)
{
    if (s->top >= s->size - 1)
        return 0; // スタックがいっぱい
        
    s->top++;
    s->data[s->top] = n;
    return 1;
}
