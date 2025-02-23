/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 18:55:38 by mirokugo          #+#    #+#             */
/*   Updated: 2025/02/23 19:18:17 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

void	validate_int(char *str)
{
	int	i;

    i = 0;
	while (str[i])
	{
		if (i == 0 && (str[i] == '-' || str[i] == '+'))
			i++;
		if (!ft_isdigit(str[i]))
		{
			write(2, "Error\n", 6);
			exit(1);
		}
        i++;
	}
}

void	validate_over_underflow(char *str)
{
	long long	num;

	num = ft_strtol(str);
	if (num > 2147483647 || num < -2147483648)
	{
		write(2, "Error\n", 6);
		exit(1);
	}
}

void	validate_duplicated(t_stack *stack, int n)
{
	int	i;

	i = 0;
	while (i < stack->top)
	{
		if (stack->data[i] == n)
		{
			write(2, "Error\n", 6);
			exit(1);
		}
		i++;
	}
}

void	validate_input(char *str, t_stack *stack)
{
	validate_int(str);
	validate_over_underflow(str);
	validate_duplicated(stack, ft_atoi(str));
}