/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 21:03:25 by mirokugo          #+#    #+#             */
/*   Updated: 2025/02/18 21:11:53 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/push_swap.h"
# include <string.h>

char *capture_stdout(void (*f)(t_stack *), t_stack *stack)
{
    int fd[2];
    int save;
    char *buf = NULL;
    int len;

    pipe(fd);
    save = dup(1);
    dup2(fd[1], 1);
    close(fd[1]);
    f(stack);
    dup2(save, 1);
    len = read(fd[0], buf, 1000);
    buf = (char *)malloc(sizeof(char) * (len + 1));
    read(fd[0], buf, len);
    buf[len] = '\0';
    close(fd[0]);
    return (buf);
}

char *display_test(void)
{
    int i;
    t_stack stack_a;
    t_stack stack_b;
    char *output;

    stack_a.data = (int *)malloc(sizeof(int) * 3);
    stack_b.data = (int *)malloc(sizeof(int) * 3);

    init(&stack_a);
    init(&stack_b);

    i = 0;
    stack_a.data[++stack_a.top] = 1;
    stack_a.data[++stack_a.top] = 2;
    stack_a.data[++stack_a.top] = 3;

    push_atob(&stack_a, &stack_b);
    push_atob(&stack_a, &stack_b);

    display_stack(&stack_a);
    display_stack(&stack_b);

    output = capture_stdout(display_stack, &stack_a);
    if (strcmp(output, "stack contents : \n3\n2\n1\n") != 0)
        return (strdup("display_stack test 1 failed"));
    free(output);

    output = capture_stdout(display_stack, &stack_b);
    if (strcmp(output, "stack contents : \n2\n1\n") != 0)
        return (strdup("display_stack test 2 failed"));
    free(output);

    return (NULL);
}