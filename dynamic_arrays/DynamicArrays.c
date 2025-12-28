// 動的配列
#include <stdio.h>
#include <stdlib.h>

// 動的配列を表す構造体
typedef struct {
    int * items;        // 整数型の配列へのポインタ
    size_t count;       // 現在格納されている要素数
    size_t capacity;    // 配列の容量（確保済みのメモリサイズ）
} Numbers;

int main(void)
{
    // 動的配列の初期化（すべてのフィールドを0で初期化）
    Numbers xs = {0};
    
    // 0から9までの数値を動的配列に追加
    for(int x = 0; x < 10; ++x) {
        // 要素数が容量に達した場合、メモリを拡張
        if(xs.count >= xs. capacity) {
            // 初回は容量を256に設定
            if(xs.capacity == 0) xs.capacity = 256;
            // 2回目以降は容量を2倍にする
            else xs.capacity *= 2;
            // reallocで配列のメモリを再確保
            xs.items = realloc(xs.items, xs.capacity * sizeof(*xs.items));
        }  
        // 配列に値を追加し、要素数をインクリメント
        xs.items[xs.count++] = x;
    }
    
    // 配列のすべての要素を出力
    for (size_t i = 0; i < xs. count; ++i) printf("%d\n", xs.items[i]);
    
    return 0;
}
