/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lis_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 22:30:00 by mirokugo          #+#    #+#             */
/*   Updated: 2025/06/03 22:30:00 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

static int	*find_lis(t_stack *stack, int *lis_len)
{
	int	*lis;
	int	*dp;
	int	*parent;
	int	i;
	int	j;
	int	max_len;
	int	max_idx;

	int size = stack->top + 1;
	lis = (int *)ft_calloc(size, sizeof(int));
	dp = (int *)ft_calloc(size, sizeof(int));
	parent = (int *)ft_calloc(size, sizeof(int));
	
	if (!lis || !dp || !parent)
		return (NULL);

	// Initialize
	i = 0;
	while (i < size)
	{
		dp[i] = 1;
		parent[i] = -1;
		i++;
	}

	// Find LIS using dynamic programming
	max_len = 1;
	max_idx = 0;
	i = 1;
	while (i < size)
	{
		j = 0;
		while (j < i)
		{
			if (stack->data[stack->top - j] < stack->data[stack->top - i] && dp[j] + 1 > dp[i])
			{
				dp[i] = dp[j] + 1;
				parent[i] = j;
			}
			j++;
		}
		if (dp[i] > max_len)
		{
			max_len = dp[i];
			max_idx = i;
		}
		i++;
	}

	// Reconstruct LIS
	*lis_len = max_len;
	int curr = max_idx;
	i = max_len - 1;
	while (curr != -1 && i >= 0)
	{
		lis[i] = curr;
		curr = parent[curr];
		i--;
	}

	free(dp);
	free(parent);
	return (lis);
}

static int	is_in_lis(int pos, int *lis, int lis_len)
{
	int	i;

	i = 0;
	while (i < lis_len)
	{
		if (lis[i] == pos)
			return (1);
		i++;
	}
	return (0);
}

static void	push_non_lis_to_b(t_stack *a, t_stack *b, int *lis, int lis_len)
{
	int	size;
	int	pushed;
	int	pos;

	size = a->top + 1;
	pushed = 0;
	pos = 0;

	while (pushed < size - lis_len)
	{
		if (!is_in_lis(pos, lis, lis_len))
		{
			push_atob(a, b);
			pushed++;
		}
		else
			rotate_a(a);
		pos++;
		if (pos >= size)
			pos = 0;
	}
}

static void	smart_push_back_lis(t_stack *a, t_stack *b)
{
	int	max_val;
	int	max_pos;
	int	size;
	int	i;

	while (b->top >= 0)
	{
		size = b->top + 1;
		max_val = b->data[0];
		max_pos = 0;

		// Find maximum value in stack B
		i = 0;
		while (i <= b->top)
		{
			if (b->data[i] > max_val)
			{
				max_val = b->data[i];
				max_pos = i;
			}
			i++;
		}

		// Rotate to bring max to top
		if (max_pos <= size / 2)
		{
			while (max_pos > 0)
			{
				rotate_b(b);
				max_pos--;
			}
		}
		else
		{
			while (max_pos < size)
			{
				reverse_rotate_b(b);
				max_pos++;
			}
		}

		push_btoa(b, a);
	}
}

void	lis_sort(t_stack *stack_a, t_stack *stack_b)
{
	int	*lis;
	int	lis_len;

	if (stack_a->top < 1)
		return;

	rank_normalize(stack_a);
	
	lis = find_lis(stack_a, &lis_len);
	if (!lis)
		return;

	push_non_lis_to_b(stack_a, stack_b, lis, lis_len);
	smart_push_back_lis(stack_a, stack_b);

	free(lis);
}