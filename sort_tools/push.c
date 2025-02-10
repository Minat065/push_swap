/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:55:16 by mirokugo          #+#    #+#             */
/*   Updated: 2025/02/10 17:56:20 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sort_tools/sort_tools.h"

int	push(t_stack *s, int value)
{
	if (s->top >= MAX_SIZE - 1)
	{
		printf("stack is overflow");
		return (-1);
	}
	s->data[++(s->top)] = value;
	return (0);
}
