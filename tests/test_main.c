/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 21:40:10 by mirokugo          #+#    #+#             */
/*   Updated: 2025/02/18 17:28:25 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include	"../src/utils_libft/libft.h"
#include	"../includes/push_swap.h"

int	is_emty(t_stack *s)
{
	return (s->top == -1);
}

int	main(int argc, char *argv[])
{
	int	i;
	t_stack stack_a;
	t_stack stack_b;

	init(&stack_a);
	init(&stack_b);

	if (argc < 2)
	{
		printf("コマンドライン引数が不足している");
		return 1;
	}

	i = 0;
	while (i < argc)
	{
		stack_a.data[++stack_a.top] = ft_atoi(&argv[i][0]);
		i++;
	}
	
	ft_printf("swap\n");
	ft_printf("stack a: ");
	display_stack(&stack_a);

	ft_printf("stack b: ");
	display_stack(&stack_b);

	ft_printf("push a to b\n");
	push_atob(&stack_a, &stack_b);

	ft_printf("stack a: ");
	display_stack(&stack_a);

	ft_printf("stack b: ");
	display_stack(&stack_b);
	return 0;
}

