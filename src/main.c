/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:48:16 by mirokugo          #+#    #+#             */
/*   Updated: 2025/02/23 20:44:20 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//最初はここで大まかな設計を考える
//なので、中身はさておき、関数名や引数、戻り値の型を決める
//関数の中身は後で考える
//関数の中身を考えるときは、テストを書いてから考える
//テストを書くときは、どのような入力に対してどのような出力が欲しいかを考える
//テストを書いたら、そのテストを通すように関数を実装する

#include "../includes/push_swap.h"

int main(int argc, char **argv)
{
	t_stack stack_a;
	t_stack stack_b;

    if (argc < 2)
        exit(1);

    init_stack(&stack_a, argc - 1);
    init_stack(&stack_b, argc - 1);
    init_a_input_elements(&stack_a, argc, argv);

    //push_swap(&stack_a, &stack_b);

    display_stack(&stack_a);

    reverse_rotate_a(&stack_a);
    display_stack(&stack_a);

    swap_a(&stack_a);
    display_stack(&stack_a);

    rotate_a(&stack_a);
    display_stack(&stack_a);
    display_stack(&stack_b);

    push_atob(&stack_a, &stack_b);
    push_atob(&stack_a, &stack_b);
    push_atob(&stack_a, &stack_b);
    display_stack(&stack_a);
    display_stack(&stack_b);

    

    free(stack_a.data);
    free(stack_b.data);

    return (0);
}