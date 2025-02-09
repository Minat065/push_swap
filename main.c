/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 21:40:10 by mirokugo          #+#    #+#             */
/*   Updated: 2025/02/09 21:46:25 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include	"./src/libft.h"

#define MAX_SIZE 100

typedef struct s_stack
{
	int	data[MAX_SIZE];
	int	top;
}	t_Stack;

void	inin(Stack *s)
{
	s->top = -1;
}

int	is_emty(Stack *s)
{
	return (s->top == -1);
}
