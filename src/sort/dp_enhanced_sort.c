/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dp_enhanced_sort.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minato <minato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 20:00:00 by minato            #+#    #+#             */
/*   Updated: 2025/01/06 20:00:00 by minato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"
#include <limits.h>

#define MAX_SMALL_SIZE 12
#define MAX_MEMO_ENTRIES 10000

typedef struct s_state_key
{
	int		size;
	int		elements[MAX_SMALL_SIZE];
	int		hash;
}	t_state_key;

typedef struct s_memo_entry
{
	t_state_key	key;
	int			min_ops;
	int			best_operation;
	int			valid;
}	t_memo_entry;

static t_memo_entry	memo_table[MAX_MEMO_ENTRIES];
static int			memo_initialized = 0;

static int	simple_hash(t_state_key *key)
{
	int	hash = key->size;
	int	i;

	for (i = 0; i < key->size; i++)
		hash = (hash * 31 + key->elements[i]) % MAX_MEMO_ENTRIES;
	return (hash < 0) ? -hash : hash;
}

static int	keys_equal(t_state_key *k1, t_state_key *k2)
{
	int	i;

	if (k1->size != k2->size)
		return (0);
	for (i = 0; i < k1->size; i++)
	{
		if (k1->elements[i] != k2->elements[i])
			return (0);
	}
	return (1);
}

static void	create_state_key(t_stack *stack, t_state_key *key, int max_size)
{
	int	size = stack->top + 1;
	int	i;

	if (size > max_size)
		size = max_size;
	
	key->size = size;
	for (i = 0; i < size; i++)
		key->elements[i] = stack->data[stack->top - i];
	
	key->hash = simple_hash(key);
}

static int	is_small_sorted(t_state_key *key)
{
	int	i;

	for (i = 1; i < key->size; i++)
	{
		if (key->elements[i-1] > key->elements[i])
			return (0);
	}
	return (1);
}

static void	apply_operation(t_state_key *key, int op, t_state_key *result)
{
	int	i;

	*result = *key;
	
	switch (op)
	{
		case 0: // sa
			if (result->size >= 2)
			{
				int temp = result->elements[0];
				result->elements[0] = result->elements[1];
				result->elements[1] = temp;
			}
			break;
		case 1: // ra
			if (result->size >= 2)
			{
				int temp = result->elements[0];
				for (i = 0; i < result->size - 1; i++)
					result->elements[i] = result->elements[i + 1];
				result->elements[result->size - 1] = temp;
			}
			break;
		case 2: // rra
			if (result->size >= 2)
			{
				int temp = result->elements[result->size - 1];
				for (i = result->size - 1; i > 0; i--)
					result->elements[i] = result->elements[i - 1];
				result->elements[0] = temp;
			}
			break;
	}
	result->hash = simple_hash(result);
}

static int	lookup_memo(t_state_key *key)
{
	int	index = key->hash;
	int	original_index = index;

	do {
		if (memo_table[index].valid && keys_equal(&memo_table[index].key, key))
			return (memo_table[index].min_ops);
		
		index = (index + 1) % MAX_MEMO_ENTRIES;
	} while (index != original_index);
	
	return (-1);
}

static void	store_memo(t_state_key *key, int min_ops, int best_op)
{
	int	index = key->hash;
	int	original_index = index;

	do {
		if (!memo_table[index].valid)
		{
			memo_table[index].key = *key;
			memo_table[index].min_ops = min_ops;
			memo_table[index].best_operation = best_op;
			memo_table[index].valid = 1;
			return;
		}
		index = (index + 1) % MAX_MEMO_ENTRIES;
	} while (index != original_index);
}

static int	dp_solve_small(t_state_key *key, int depth, int max_depth)
{
	int			cached;
	t_state_key	next_state;
	int			min_ops;
	int			ops;
	int			i;

	if (depth > max_depth)
		return (999);
	
	if (is_small_sorted(key))
		return (0);
	
	cached = lookup_memo(key);
	if (cached != -1)
		return (cached);
	
	min_ops = 999;
	
	for (i = 0; i < 3; i++)
	{
		apply_operation(key, i, &next_state);
		ops = 1 + dp_solve_small(&next_state, depth + 1, max_depth);
		if (ops < min_ops)
			min_ops = ops;
	}
	
	if (depth <= 5)
		store_memo(key, min_ops, 0);
	
	return (min_ops);
}

static int	estimate_remaining_ops(t_stack *a, t_stack *b)
{
	int	inversions = 0;
	int	i, j;
	
	for (i = 0; i <= a->top; i++)
	{
		for (j = i + 1; j <= a->top; j++)
		{
			if (a->data[i] > a->data[j])
				inversions++;
		}
	}
	
	for (i = 0; i <= b->top; i++)
	{
		for (j = i + 1; j <= b->top; j++)
		{
			if (b->data[i] < b->data[j])
				inversions++;
		}
	}
	
	return (inversions / 3 + (b->top + 1) * 2);
}

static int	dp_guided_move_selection(t_stack *a, t_stack *b)
{
	t_state_key	a_key;
	int			a_size = a->top + 1;
	int			best_cost = 999;
	int			best_move = -1;
	
	if (a_size <= MAX_SMALL_SIZE && a_size >= 3)
	{
		create_state_key(a, &a_key, MAX_SMALL_SIZE);
		int dp_cost = dp_solve_small(&a_key, 0, 8);
		
		if (dp_cost <= 3)
		{
			return (0);
		}
	}
	
	if (b->top >= 0)
	{
		int	b_size = b->top + 1;
		int	search_limit = (b_size > 30) ? 15 : b_size;
		int	i;
		
		for (i = 0; i < search_limit; i++)
		{
			int	value = b->data[b->top - i];
			int	insert_cost = 0;
			int	b_rotation_cost = (i <= b_size / 2) ? i : b_size - i;
			
			int	j;
			for (j = 0; j <= a->top; j++)
			{
				if ((j == a->top || a->data[j] < value) && 
					(j == 0 || a->data[j-1] > value))
				{
					int a_pos = a->top - j;
					insert_cost = (a_pos <= a_size / 2) ? a_pos : a_size - a_pos;
					break;
				}
			}
			
			int	total_cost = insert_cost + b_rotation_cost + 1;
			int	future_penalty = estimate_remaining_ops(a, b) / 10;
			total_cost += future_penalty;
			
			if (total_cost < best_cost)
			{
				best_cost = total_cost;
				best_move = i;
			}
		}
	}
	
	return (best_move);
}

static void	execute_dp_guided_move(t_stack *a, t_stack *b, int b_index)
{
	int	b_size = b->top + 1;
	int	b_rotations = (b_index <= b_size / 2) ? b_index : b_size - b_index;
	int	rotate_forward = (b_index <= b_size / 2);
	
	while (b_rotations-- > 0)
	{
		if (rotate_forward)
			rotate_b(b);
		else
			reverse_rotate_b(b);
	}
	
	int	value = b->data[b->top];
	int	best_a_pos = 0;
	int	i;
	
	for (i = 0; i <= a->top; i++)
	{
		if ((i == a->top || a->data[i] < value) && 
			(i == 0 || a->data[i-1] > value))
		{
			best_a_pos = a->top - i;
			break;
		}
	}
	
	int	a_size = a->top + 1;
	int	a_rotations = (best_a_pos <= a_size / 2) ? best_a_pos : a_size - best_a_pos;
	int	a_rotate_forward = (best_a_pos <= a_size / 2);
	
	while (a_rotations-- > 0)
	{
		if (a_rotate_forward)
			rotate_a(a);
		else
			reverse_rotate_a(a);
	}
	
	push_btoa(b, a);
}

static void	dp_chunk_push(t_stack *a, t_stack *b)
{
	int	initial_size = a->top + 1;
	int	chunk_size = (initial_size <= 200) ? 28 : 38;
	int	current_chunk = 0;
	
	while (a->top > 2)
	{
		int min_val = current_chunk * chunk_size;
		int max_val = (current_chunk + 1) * chunk_size - 1;
		if (max_val >= initial_size)
			max_val = initial_size - 1;
		
		int moved = 0;
		int target_moves = max_val - min_val + 1;
		int i;
		
		for (i = 0; i < initial_size * 2 && moved < target_moves && a->top > 2; i++)
		{
			if (a->data[a->top] >= min_val && a->data[a->top] <= max_val)
			{
				push_atob(a, b);
				moved++;
			}
			else
				rotate_a(a);
		}
		current_chunk++;
	}
}

void	dp_enhanced_sort(t_stack *a, t_stack *b)
{
	if (!memo_initialized)
	{
		int i;
		for (i = 0; i < MAX_MEMO_ENTRIES; i++)
			memo_table[i].valid = 0;
		memo_initialized = 1;
	}
	
	rank_normalize(a);
	dp_chunk_push(a, b);
	sort_three(a);
	
	while (b->top >= 0)
	{
		int best_move = dp_guided_move_selection(a, b);
		if (best_move >= 0)
			execute_dp_guided_move(a, b, best_move);
		else
			push_btoa(b, a);
	}
	
	int min_pos = 0;
	int min_val = INT_MAX;
	int size = a->top + 1;
	int i;
	
	for (i = 0; i <= a->top; i++)
	{
		if (a->data[i] < min_val)
		{
			min_val = a->data[i];
			min_pos = i;
		}
	}
	
	int final_pos = a->top - min_pos;
	int final_rotations = (final_pos <= size / 2) ? final_pos : size - final_pos;
	int final_forward = (final_pos <= size / 2);
	
	while (final_rotations-- > 0)
	{
		if (final_forward)
			rotate_a(a);
		else
			reverse_rotate_a(a);
	}
}