/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by student           #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

static void	cleanup_and_exit(t_stack *a, t_stack *b, int *numbers)
{
	free(numbers);
	if (a)
		free_stack(a);
	if (b)
		free_stack(b);
	error_exit();
}

static int	initialize_stacks(t_stack **a, t_stack **b, int *numbers)
{
	*a = init_stack();
	*b = init_stack();
	if (!*a || !*b)
	{
		cleanup_and_exit(*a, *b, numbers);
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_stack	*a;
	t_stack	*b;
	int		*numbers;
	int		size;

	if (argc < 2)
		return (0);
	numbers = parse_arguments(argc, argv, &size);
	if (!numbers)
		return (1);
	if (!initialize_stacks(&a, &b, numbers))
		return (1);
	fill_stack(a, numbers, size);
	free(numbers);
	if (!is_sorted(a))
		push_swap(a, b);
	free_stack(a);
	free_stack(b);
	return (0);
}
