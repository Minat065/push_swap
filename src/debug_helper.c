/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 23:45:00 by mirokugo          #+#    #+#             */
/*   Updated: 2025/06/03 23:45:00 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"
#include <stdio.h>

void debug_print_stacks(t_stack *a, t_stack *b, const char *phase)
{
    int i;
    
    printf("\n=== %s ===\n", phase);
    printf("Stack A (size %d): ", a->top + 1);
    if (a->top >= 0)
    {
        for (i = a->top; i >= 0; i--)
            printf("%d ", a->data[i]);
    }
    else
        printf("empty");
    
    printf("\nStack B (size %d): ", b->top + 1);
    if (b->top >= 0)
    {
        for (i = b->top; i >= 0; i--)
            printf("%d ", b->data[i]);
    }
    else
        printf("empty");
    printf("\n");
}

int is_stack_sorted(t_stack *a)
{
    int i;
    
    if (a->top < 1)
        return (1);
    
    for (i = a->top; i > 0; i--)
    {
        if (a->data[i] > a->data[i - 1])
            return (0);
    }
    return (1);
}

void debug_verify_sort(t_stack *a, t_stack *b)
{
    printf("\n=== FINAL VERIFICATION ===\n");
    debug_print_stacks(a, b, "Final State");
    
    if (b->top >= 0)
    {
        printf("ERROR: Stack B is not empty!\n");
        return;
    }
    
    if (is_stack_sorted(a))
        printf("SUCCESS: Stack A is properly sorted!\n");
    else
        printf("ERROR: Stack A is NOT sorted!\n");
}