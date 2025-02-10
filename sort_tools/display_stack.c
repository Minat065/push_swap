/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_stack.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:57:57 by mirokugo          #+#    #+#             */
/*   Updated: 2025/02/10 17:59:38 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../sort_tools/sort_tools.h"

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
	while (i > 0)
	{
		printf("%d\n", s->data[i]);
		i--;
	}
}
