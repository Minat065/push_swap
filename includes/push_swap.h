/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:26:30 by mirokugo          #+#    #+#             */
/*   Updated: 2025/02/23 19:22:01 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "../src/utils_libft/libft.h"
# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_stack
{
    int	*data;
    int	top;
}	t_stack;

void	init_stack(t_stack *s, int size);
void	display_stack(t_stack *s);
int     push(t_stack *s, int n);
int     pop(t_stack *s);
void    swap(t_stack *s);
int     push_atob(t_stack *src, t_stack *dst);
int     push_btoa(t_stack *src, t_stack *dst);
void    validate_input(char *str, t_stack *stack);
void    init_a_input_elements(t_stack *stack_a, int argc, char **argv);
void    push_swap(t_stack *stack_a, t_stack *stack_b);
//long   ft_strtol(const char *str);


#endif