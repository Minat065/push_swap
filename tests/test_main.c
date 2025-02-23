/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 21:40:10 by mirokugo          #+#    #+#             */
/*   Updated: 2025/02/21 18:55:22 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include	"../src/utils_libft/libft.h"
#include	"../includes/push_swap.h"
#include	"../includes/tests.h"

int	main(int argc, char *argv[])
{
	int	i;
	t_stack stack_a;
	t_stack stack_b;

	init(&stack_a);
	init(&stack_b);

	if (argc < 2)
	{
		printf("command line arguments are missing");
		return 1;
	}

	stack_a.data = (int *)malloc(sizeof(int) * argc);
	stack_b.data = (int *)malloc(sizeof(int) * argc);

	i = 0;
	while (i < argc)
	{
		stack_a.data[++stack_a.top] = ft_atoi(&argv[i][0]);
		i++;
	}

	test_display_stack_when_stack_is_empty(&stack_a);
	test_display_stack_when_stack_has_one_element(&stack_a);
	test_display_stack_when_stack_has_two_elements(&stack_a);
	test_display_stack_when_stack_has_three_elements(&stack_a);
	test_display_stack_when_stack_has_four_elements(&stack_a);

	return 0;
}

