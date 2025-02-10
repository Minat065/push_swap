/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 21:40:10 by mirokugo          #+#    #+#             */
/*   Updated: 2025/02/10 20:05:56 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include	"./utils/libft.h"
#include	"./sort_tools/sort_tools.h"

int	is_emty(t_stack *s)
{
	return (s->top == -1);
}

int	main(int argc, char *argv[])
{
	int	i;
	t_stack stack;

	init(&stack);

	if (argc < 2)
	{
		printf("コマンドライン引数が不足している");
		return 1;
	}

	i = 0;
	while (i < argc)
	{
		stack.data[++stack.top] = ft_atoi(&argv[i][0]);
		i++;
	}

	swap(&stack);
	display_stack(&stack);

	return 0;
}

