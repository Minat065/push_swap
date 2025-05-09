/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_to_another.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 20:35:35 by mirokugo          #+#    #+#             */
/*   Updated: 2025/03/12 17:08:14 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"
#include	"../utils_libft/libft.h"

// 修正後の push_atob 関数
int push_atob(t_stack *src, t_stack *dst)
{
    if (src->top == -1)
        return (1);
    push(dst, src->data[src->top]);
    src->top--;
    ft_printf("pb\n");  // pa から pb に修正

    return (0);
}

// 修正後の push_btoa 関数
int push_btoa(t_stack *src, t_stack *dst)
{
    if (src->top == -1)
        return (1);
    push(dst, src->data[src->top]);
    src->top--;
    ft_printf("pa\n");  // pb から pa に修正

    return (0);
}
