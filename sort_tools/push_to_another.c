/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_to_another.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 20:35:35 by mirokugo          #+#    #+#             */
/*   Updated: 2025/02/10 20:52:05 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../sort_tools/sort_tools.h"
#include	"../utils/libft.h"

int     push_to_another(t_stack *src, t_stack *dst)
{
    if (src->top == -1)
        return (0);
    push(dst, src->data[src->top]);
    src->top--;
    return (1);
}