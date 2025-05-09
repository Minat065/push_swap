#!/bin/bash

# コンパイル
make re

# 色の定義
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

# テスト関数
run_test() {
    echo -e "\n${GREEN}テスト: $1${NC}"
    echo "コマンド: $2"
    eval "$2"
    echo "終了コード: $?"
    echo "------------------------"
}

# 正常系テスト
echo -e "\n${GREEN}=== 正常系テスト ===${NC}"

# 単一の数値
run_test "単一の数値" "./push_swap 42"

# 複数の数値
run_test "複数の数値" "./push_swap 1 2 3 4 5"

# 空白区切りの数値列
run_test "空白区切りの数値列" "./push_swap \"1 2 3 4 5\""

# 大きな数値
run_test "大きな数値" "./push_swap 2147483647 2147483646 2147483645"

# 小さな数値
run_test "小さな数値" "./push_swap -2147483648 -2147483647 -2147483646"

# 異常系テスト
echo -e "\n${GREEN}=== 異常系テスト ===${NC}"

# 空の入力
run_test "空の入力" "./push_swap"

# 不正な入力（非数値）
run_test "非数値" "./push_swap abc"

# 重複値
run_test "重複値" "./push_swap 1 1 2 3"

# オーバーフロー値
run_test "オーバーフロー値" "./push_swap 2147483648"

# アンダーフロー値
run_test "アンダーフロー値" "./push_swap -2147483649"

# 複合テスト
echo -e "\n${GREEN}=== 複合テスト ===${NC}"

# 100個のランダムな数値
run_test "100個のランダムな数値" "python3 -c 'import random; print(\" \".join(map(str, random.sample(range(1, 101), 100))))' | xargs ./push_swap"

# 500個のランダムな数値
run_test "500個のランダムな数値" "python3 -c 'import random; print(\" \".join(map(str, random.sample(range(1, 501), 500))))' | xargs ./push_swap"

# メモリリークチェック
echo -e "\n${GREEN}=== メモリリークチェック ===${NC}"
run_test "メモリリークチェック" "valgrind --leak-check=full ./push_swap 1 2 3 4 5" 