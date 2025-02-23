/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_a_input_elements.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 18:54:09 by mirokugo          #+#    #+#             */
/*   Updated: 2025/02/23 19:09:38 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

void    init_a_input_elements(t_stack *stack_a, int argc, char **argv)
{
    int i;

    i = 1;
    while (i < argc)
    {
        validate_input(argv[argc - i], stack_a);
        push(stack_a, ft_atoi(argv[argc - i]));
        i++;
    }
}