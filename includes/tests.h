/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 18:28:29 by mirokugo          #+#    #+#             */
/*   Updated: 2025/02/21 18:55:37 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_H
# define TESTS_H

# include "push_swap.h"

void test_display_stack_when_stack_is_empty(t_stack *s);
void test_display_stack_when_stack_has_one_element(t_stack *s);
void test_display_stack_when_stack_has_two_elements(t_stack *s);
void test_display_stack_when_stack_has_three_elements(t_stack *s);
void test_display_stack_when_stack_has_four_elements(t_stack *s);

#endif