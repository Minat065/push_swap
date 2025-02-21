/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_stack.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:57:57 by mirokugo          #+#    #+#             */
/*   Updated: 2025/02/18 18:28:48 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../../includes/push_swap.h"

void	display_stack(t_stack *s)
{
	int	i;

	if (s->top < 0)
	{
		printf("stack is empty");
		return ;
	}
	printf("stack contents : \n");
	i = s->top;
	while (i >= 0)
	{
		printf("%d\n", s->data[i]);
		printf("i = %d\n", i);
		i--;
	}
}
