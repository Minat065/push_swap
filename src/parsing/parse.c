/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by student           #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

int	validate_number(const char *str)
{
	int		i;
	long	num;

	if (!str || !*str)
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		i++;
		if (!str[i])
			return (0);
	}
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	num = ft_atol(str);
	if (num > INT_MAX || num < INT_MIN)
		return (0);
	return (1);
}

static int	*parse_single_string(char *str, int *size)
{
	char	**split;
	int		*result;

	split = ft_split(str, ' ');
	if (!split)
		return (NULL);
	*size = count_split_size(split);
	if (*size == 0)
	{
		free_split(split);
		return (NULL);
	}
	result = convert_split_to_int_array(split, *size);
	free_split(split);
	return (result);
}

static int	*handle_single_arg(char *arg, int *size)
{
	int	*result;

	result = parse_single_string(arg, size);
	if (!result || check_duplicates(result, *size))
	{
		if (result)
			free(result);
		error_exit();
		return (NULL);
	}
	return (result);
}

static int	*parse_multi_args(int argc, char **argv, int *size)
{
	int	*result;
	int	i;

	*size = argc - 1;
	result = malloc(sizeof(int) * (*size));
	if (!result)
		return (NULL);
	i = 0;
	while (i < *size)
	{
		if (!validate_number(argv[i + 1]))
		{
			free(result);
			error_exit();
			return (NULL);
		}
		result[i] = (int)ft_atol(argv[i + 1]);
		i++;
	}
	return (result);
}

int	*parse_arguments(int argc, char **argv, int *size)
{
	int	*result;

	if (argc < 2)
		return (NULL);
	if (argc == 2)
		return (handle_single_arg(argv[1], size));
	result = parse_multi_args(argc, argv, size);
	if (!result)
		return (NULL);
	if (check_duplicates(result, *size))
	{
		free(result);
		error_exit();
		return (NULL);
	}
	return (result);
}
