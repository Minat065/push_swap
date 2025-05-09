/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:26:30 by mirokugo          #+#    #+#             */
/*   Updated: 2025/03/12 16:27:03 by mirokugo         ###   ########.fr       */
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
    int	size;
}	t_stack;

void	init_stack(t_stack *s, int size);
void	display_stack(t_stack *a, t_stack *b);
int     push(t_stack *s, int n);
int     pop(t_stack *s);
void    swap(t_stack *s);
int     push_atob(t_stack *src, t_stack *dst);
int     push_btoa(t_stack *src, t_stack *dst);
void    validate_input(char *str, t_stack *stack);
void    init_a_input_elements(t_stack *stack_a, int argc, char **argv);
void    push_swap(t_stack *stack_a, t_stack *stack_b);
int     find_min(t_stack *stack_a);
int     find_max(t_stack *stack_a);
void    sort_small(t_stack *stack_a, t_stack *stack_b);
void    sort_three(t_stack *stack_a);
void    sort_four_five(t_stack *stack_a, t_stack *stack_b);
int     find_min_position(t_stack *stack_a);
void    swap_a(t_stack *stack_a);
void    swap_b(t_stack *stack_b);
void    rotate_a(t_stack *stack_a);
void    rotate_b(t_stack *stack_b);
void    reverse_rotate_a(t_stack *stack_a);
void    reverse_rotate_b(t_stack *stack_b);
void    quick_sort(int *arr, int low, int high);
int     partition(int *arr, int low, int high);
void    rank_normalize(t_stack *stack);
int     is_sorted(t_stack *stack);
void    radix_sort(t_stack *stack_a, t_stack *stack_b);
void    restore_original_values(t_stack *stack, int *original_values);


#endif