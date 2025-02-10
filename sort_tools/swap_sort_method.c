/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_sort_method.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 20:00:48 by mirokugo          #+#    #+#             */
/*   Updated: 2025/02/10 20:07:05 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include	"../utils/libft.h"
#include	"../sort_tools/sort_tools.h"

void    swap(t_stack *s)
{
    int tmp;

    if (s->top <= 1)
        return ;

    tmp = s->data[s->top];
    s->data[s->top] = s->data[s->top - 1];
    s->data[s->top - 1] = tmp;
}