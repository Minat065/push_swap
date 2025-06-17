/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   target_finder2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by student           #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

void	smart_push_large(t_stack *a, t_stack *b)
{
	int	push_count;
	int	median;

	push_count = a->size - 3;
	if (push_count <= 0)
		return ;
	assign_indices(a);
	median = a->size / 2;
	push_small_elements(a, b, &push_count, median);
	while (a->size > 3)
		pb(a, b, 1);
}
