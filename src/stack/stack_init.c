/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by student           #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

t_stack	*init_stack(void)
{
	t_stack	*stack;

	stack = malloc(sizeof(t_stack));
	if (!stack)
		return (NULL);
	stack->top = NULL;
	stack->bottom = NULL;
	stack->size = 0;
	return (stack);
}

t_node	*create_node(int value)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->value = value;
	node->index = 0;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	fill_stack(t_stack *stack, int *arr, int size)
{
	t_node	*node;
	int		i;

	if (!stack || !arr)
		return ;
	i = size - 1;
	while (i >= 0)
	{
		node = create_node(arr[i]);
		if (!node)
		{
			free_stack(stack);
			error_exit();
		}
		node->next = stack->top;
		if (stack->top)
			stack->top->prev = node;
		stack->top = node;
		if (!stack->bottom)
			stack->bottom = node;
		stack->size++;
		i--;
	}
}
