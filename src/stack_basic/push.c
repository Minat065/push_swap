/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:55:16 by mirokugo          #+#    #+#             */
/*   Updated: 2025/02/18 17:58:15 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

int	push(t_stack *s, int value)
{
	// if (s->top >= MAX_SIZE - 1)
	// {
	// 	printf("stack is overflow");
	// 	return (-1);
	// }
	s->data[++(s->top)] = value;
	return (0);
}
