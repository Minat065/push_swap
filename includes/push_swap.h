/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 01:04:34 by mirokugo          #+#    #+#             */
/*   Updated: 2025/06/17 01:04:53 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include "../src/libft/libft.h"

typedef struct s_node
{
	int				value;
	int				index;
	struct s_node	*next;
	struct s_node	*prev;
}	t_node;

typedef struct s_stack
{
	t_node	*top;
	t_node	*bottom;
	int		size;
}	t_stack;

typedef struct s_cost
{
	int	a_moves;
	int	b_moves;
	int	total;
	int	b_index;
}	t_cost;

/* Parse and validation */
int		*parse_arguments(int argc, char **argv, int *size);
int		validate_number(const char *str);
int		check_duplicates(int *arr, int size);
long	ft_atol(const char *str);

/* Error handling */
void	error_exit(void);
void	free_stack(t_stack *stack);
void	free_split(char **split);

/* Stack initialization and utilities */
t_stack	*init_stack(void);
void	fill_stack(t_stack *stack, int *arr, int size);
int		is_sorted(t_stack *stack);
int		get_stack_size(t_stack *stack);
t_node	*create_node(int value);

/* Stack operations - swap */
void	sa(t_stack *a, int print);
void	sb(t_stack *b, int print);
void	ss(t_stack *a, t_stack *b, int print);

/* Stack operations - push */
void	pa(t_stack *a, t_stack *b, int print);
void	pb(t_stack *a, t_stack *b, int print);

/* Stack operations - rotate */
void	ra(t_stack *a, int print);
void	rb(t_stack *b, int print);
void	rr(t_stack *a, t_stack *b, int print);

/* Stack operations - reverse rotate */
void	rra(t_stack *a, int print);
void	rrb(t_stack *b, int print);
void	rrr(t_stack *a, t_stack *b, int print);

/* Sorting algorithms */
void	push_swap(t_stack *a, t_stack *b);
void	sort_two(t_stack *a);
void	sort_three(t_stack *a);
void	sort_four(t_stack *a, t_stack *b);
void	sort_five(t_stack *a, t_stack *b);

/* Cost-based sorting algorithm */
void	cost_sort(t_stack *a, t_stack *b);
void	cost_sort_optimized(t_stack *a, t_stack *b);
t_cost	calculate_cost(t_stack *a, t_stack *b, int b_pos);
int		find_target_position(t_stack *a, int value);
void	execute_moves(t_stack *a, t_stack *b, t_cost cost);
void	smart_push_large(t_stack *a, t_stack *b);
void	push_small_elements(t_stack *a, t_stack *b, int *push_count,
			int median);
int		get_element_at_position(t_stack *stack, int pos);

/* Cost calculation helpers */
void	initialize_cost(t_cost *cost, int b_pos);
void	calculate_a_moves(t_cost *cost, int target_pos, int a_size);
void	calculate_b_moves(t_cost *cost, int b_pos, int b_size);
void	calculate_abs_values(t_cost *cost, int *abs_a, int *abs_b);
void	calculate_total_cost(t_cost *cost);

/* Sort utilities */
int		find_min_position(t_stack *stack);
int		find_max_position(t_stack *stack);
void	smart_rotate_a(t_stack *a, int position);
void	smart_rotate_b(t_stack *b, int position);
t_cost	find_cheapest_move(t_stack *a, t_stack *b);

/* Index utilities */
void	assign_indices(t_stack *stack);

/* Utils */
void	free_split(char **split);
int		count_split_size(char **split);
int		*convert_split_to_int_array(char **split, int size);

#endif