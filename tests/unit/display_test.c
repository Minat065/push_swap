/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 21:03:25 by mirokugo          #+#    #+#             */
/*   Updated: 2025/02/21 18:54:25 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <assert.h>
#include "../../includes/push_swap.h"
#include "../../includes/tests.h"

void test_display_stack_when_stack_is_empty(t_stack *s)
{
    // Given
    //s->top = -1;
    // When
    display_stack(s);
    // Then
    // display "stack is empty"
}

void test_display_stack_when_stack_has_one_element(t_stack *s)
{
    // Given
    s->top = 0;
    s->data[0] = 1;
    // When
    display_stack(s);
    // Then
    // display "1"
}

void test_display_stack_when_stack_has_two_elements(t_stack *s)
{
    // Given
    s->top = 1;
    s->data[0] = 1;
    s->data[1] = 2;
    // When
    display_stack(s);
    // Then
    // display "1 2"
}

void test_display_stack_when_stack_has_three_elements(t_stack *s)
{
    // Given
    s->top = 2;
    s->data[0] = 1;
    s->data[1] = 2;
    s->data[2] = 3;
    // When
    display_stack(s);
    // Then
    // display "1 2 3"
}

void test_display_stack_when_stack_has_four_elements(t_stack *s)
{
    // Given
    s->top = 3;
    s->data[0] = 1;
    s->data[1] = 2;
    s->data[2] = 3;
    s->data[3] = 4;
    // When
    display_stack(s);
    // Then
    // display "1 2 3 4"
}