#include "../includes/push_swap.h"
#include "../includes/tests.h"
#include <time.h>
#include <stdlib.h>
#include <limits.h>

// 操作数をカウントするグローバル変数
static int operation_count = 0;

// 操作数をリセット
void reset_operation_count(void)
{
	operation_count = 0;
}

// 現在の操作数を取得
int get_operation_count(void)
{
	return operation_count;
}

// スタックサイズを取得
int stack_size(t_stack *stack)
{
	if (!stack)
		return 0;
	return stack->top + 1;
}

// ランダムな500要素の配列を生成
int *generate_random_500(void)
{
	int *arr = malloc(500 * sizeof(int));
	if (!arr)
		return NULL;
	
	// 1から500までの数値を配列に入れる
	for (int i = 0; i < 500; i++)
		arr[i] = i + 1;
	
	// Fisher-Yatesアルゴリズムでシャッフル
	srand(time(NULL));
	for (int i = 499; i > 0; i--)
	{
		int j = rand() % (i + 1);
		int temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;
	}
	
	return arr;
}

// スタッククリア関数
void clear_stack(t_stack **stack)
{
	if (stack && *stack)
	{
		if ((*stack)->data)
			free((*stack)->data);
		free(*stack);
		*stack = NULL;
	}
}

// 500要素ソートテスト
void test_500_elements_performance(void)
{
	ft_printf("=== 500要素ソートパフォーマンステスト ===\n");
	
	int total_operations = 0;
	int max_operations = 0;
	int min_operations = INT_MAX;
	int test_runs = 10;
	
	for (int run = 0; run < test_runs; run++)
	{
		// ランダムな500要素を生成
		int *random_array = generate_random_500();
		if (!random_array)
		{
			ft_printf("メモリ割り当てエラー\n");
			return;
		}
		
		// スタックを初期化
		t_stack *stack_a = malloc(sizeof(t_stack));
		t_stack *stack_b = malloc(sizeof(t_stack));
		init_stack(stack_a, 500);
		init_stack(stack_b, 500);
		
		// 配列をスタックAに変換
		for (int i = 499; i >= 0; i--)
			push(stack_a, random_array[i]);
		
		// ソート前の状態を確認
		if (is_sorted(stack_a))
		{
			ft_printf("警告: 初期状態がすでにソート済み（run %d）\n", run + 1);
			free(random_array);
			clear_stack(&stack_a);
			continue;
		}
		
		// 操作数をリセット
		reset_operation_count();
		
		// ソート実行（実際にはoptimized_sortの出力をカウントする必要がある）
		// 一時的にファイルに出力して行数をカウント
		char filename[50];
		sprintf(filename, "/tmp/push_swap_test_%d.txt", run);
		
		// 標準出力をファイルにリダイレクト
		FILE *original_stdout = stdout;
		FILE *file = fopen(filename, "w");
		stdout = file;
		
		optimized_sort(stack_a, stack_b);
		
		fclose(file);
		stdout = original_stdout;
		
		// ファイルの行数をカウント
		file = fopen(filename, "r");
		int operations = 0;
		char line[10];
		while (fgets(line, sizeof(line), file))
			operations++;
		fclose(file);
		
		// ソート後の確認
		if (!is_sorted(stack_a))
		{
			ft_printf("エラー: ソートが完了していません（run %d）\n", run + 1);
		}
		else
		{
			ft_printf("Run %d: %d operations\n", run + 1, operations);
			total_operations += operations;
			if (operations > max_operations)
				max_operations = operations;
			if (operations < min_operations)
				min_operations = operations;
		}
		
		// クリーンアップ
		free(random_array);
		clear_stack(&stack_a);
		clear_stack(&stack_b);
		remove(filename);
	}
	
	// 統計を出力
	ft_printf("\n=== 500要素テスト結果 ===\n");
	ft_printf("テスト回数: %d\n", test_runs);
	ft_printf("平均操作数: %.2f\n", (double)total_operations / test_runs);
	ft_printf("最大操作数: %d\n", max_operations);
	ft_printf("最小操作数: %d\n", min_operations);
	ft_printf("目標: < 5500 operations\n");
	
	if (max_operations < 5500)
		ft_printf("✅ テスト合格: 最大操作数が目標以下\n");
	else
		ft_printf("❌ テスト失敗: 最大操作数が目標を超過\n");
}

// 500要素の特定ケーステスト
void test_500_worst_case(void)
{
	ft_printf("=== 500要素最悪ケーステスト ===\n");
	
	// 逆順ソート（500, 499, 498, ..., 1）
	t_stack *stack_a = malloc(sizeof(t_stack));
	t_stack *stack_b = malloc(sizeof(t_stack));
	init_stack(stack_a, 500);
	init_stack(stack_b, 500);
	
	for (int i = 1; i <= 500; i++)
		push(stack_a, i);
	
	FILE *original_stdout = stdout;
	FILE *file = fopen("/tmp/push_swap_worst.txt", "w");
	stdout = file;
	
	optimized_sort(stack_a, stack_b);
	
	fclose(file);
	stdout = original_stdout;
	
	// 行数をカウント
	file = fopen("/tmp/push_swap_worst.txt", "r");
	int operations = 0;
	char line[10];
	while (fgets(line, sizeof(line), file))
		operations++;
	fclose(file);
	
	ft_printf("逆順ソート操作数: %d\n", operations);
	if (is_sorted(stack_a))
		ft_printf("✅ ソート成功\n");
	else
		ft_printf("❌ ソート失敗\n");
	
	clear_stack(&stack_a);
	clear_stack(&stack_b);
	remove("/tmp/push_swap_worst.txt");
}

int main(void)
{
	ft_printf("500要素ソートテスト開始\n");
	
	test_500_elements_performance();
	test_500_worst_case();
	
	return 0;
}