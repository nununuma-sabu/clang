#include "hash_table.h"
#include <stdio.h>

int main() {
    // キーと値の作成
    Key key1 = { .type = KEY_STRING, .str_key = "apple" };
    Value val1 = { .type = TYPE_INT, .int_val = 100 };
    insert(key1, val1);

    Key key2 = { .type = KEY_INT, .int_key = 42 };
    Value val2 = { .type = TYPE_FLOAT, .float_val = 3.14 };
    insert(key2, val2);

    Key key3 = { .type = KEY_STRING, .str_key = "flag" };
    Value val3 = { .type = TYPE_BOOL, .bool_val = 1 };
    insert(key3, val3);

    // 値の検索と表示
    Value *result = search(key1);
    if (result) {
        if (result->type == TYPE_INT) {
            printf("%s: %d\n", key1.str_key, result->int_val);
        }
    }

    result = search(key2);
    if (result) {
        if (result->type == TYPE_FLOAT) {
            printf("%d: %f\n", key2.int_key, result->float_val);
        }
    }

    result = search(key3);
    if (result) {
        if (result->type == TYPE_BOOL) {
            printf("%s: %s\n", key3.str_key, result->bool_val ? "true" : "false");
        }
    }

    free_table();  // メモリの解放
    return 0;
}