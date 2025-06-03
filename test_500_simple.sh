#!/bin/bash

echo "=== 500要素ソートテスト ==="

# 平均操作数を測定
total=0
runs=10

for i in $(seq 1 $runs); do
    echo -n "Test $i: "
    ops=$(python3 -c "import random; print(' '.join(map(str, random.sample(range(1, 501), 500))))" | xargs ./push_swap | wc -l)
    echo "$ops operations"
    total=$((total + ops))
done

avg=$((total / runs))
echo ""
echo "平均操作数: $avg"
echo "目標: < 5500"

if [ $avg -lt 5500 ]; then
    echo "✅ 目標達成"
else
    echo "❌ 目標未達成 (差: $((avg - 5500)))"
fi