/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:26:30 by mirokugo          #+#    #+#             */
/*   Updated: 2025/02/17 16:29:32 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SORT_TOOLS_H
# define SORT_TOOLS_H

# define MAX_SIZE 100

# include "../src/utils_libft/libft.h"
# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_stack
{
    int	data[MAX_SIZE];
    int	top;
}	t_stack;

void	init(t_stack *s);
void	display_stack(t_stack *s);
int     push(t_stack *s, int n);
int     pop(t_stack *s);
void    swap(t_stack *s);

#endif