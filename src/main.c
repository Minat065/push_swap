/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:48:16 by mirokugo          #+#    #+#             */
/*   Updated: 2025/03/12 16:51:06 by mirokugo         ###   ########.fr       */
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
    
    // 引数チェック
    if (argc < 2)
        return (0);
    
    // スタックの初期化
    init_stack(&stack_a, argc - 1);
    init_stack(&stack_b, argc - 1);
    
    // 入力要素をスタックAに格納
    init_a_input_elements(&stack_a, argc, argv);
    
    // ソートアルゴリズムの実行
    push_swap(&stack_a, &stack_b);
    
    // メモリの解放
    free(stack_a.data);
    free(stack_b.data);
    
    return (0);
}