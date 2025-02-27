/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_stack.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:57:57 by mirokugo          #+#    #+#             */
/*   Updated: 2025/02/24 18:15:54 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../../includes/push_swap.h"

void	display_stack(t_stack *a, t_stack *b)
{
	int	i, j;

	ft_printf("stack contents : \n");
	i = a->top;
	j = b->top;
	while (i >= 0 || j >= 0)
	{
		if (i >= 0)
			ft_printf("%d", a->data[i]);
		else
			ft_printf(" ");
		ft_printf(" | ");
		if (j >= 0)
			ft_printf("%d", b->data[j]);
		else
			ft_printf(" ");
		ft_printf("\n");
		i--;
		j--;
	}
	ft_printf("a | b\n");
}
