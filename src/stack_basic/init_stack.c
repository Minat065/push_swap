/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:53:40 by mirokugo          #+#    #+#             */
/*   Updated: 2025/03/12 16:00:27 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

void init_stack(t_stack *s, int size)
{
    s->data = (int *)malloc(sizeof(int) * size);
    if (s->data == NULL)
    {
        write(2, "Error\n", 6);
        exit(EXIT_FAILURE);
    }
    s->top = -1;
    s->size = size;
}
