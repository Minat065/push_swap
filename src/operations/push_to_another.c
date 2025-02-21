/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_to_another.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 20:35:35 by mirokugo          #+#    #+#             */
/*   Updated: 2025/02/18 18:21:17 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"
#include	"../utils_libft/libft.h"
int push_atob(t_stack *src, t_stack *dst)
{
    if (src->top == -1)
        return (1);
    push(dst, src->data[src->top]);
    src->top--;
    ft_printf("pa\n");

    return (0);
}

int push_btoa(t_stack *src, t_stack *dst)
{
    if (src->top == -1)
        return (1);
    push(dst, src->data[src->top]);
    src->top--;
    ft_printf("pb\n");

    return (0);
}
