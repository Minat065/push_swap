/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pop.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:56:41 by mirokugo          #+#    #+#             */
/*   Updated: 2025/02/17 16:43:11 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

int	pop(t_stack *s)
{
	if (s->top < 0)
	{
		printf("スタックのアンダーフロー");
		return (-1);
	}
	return (s->data[(s->top)--]);
}
