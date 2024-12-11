#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdio.h>

#define TABLE_SIZE 100

// 値の型の定義
typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_STRING,
    TYPE_BOOL
} ValueType;

typedef struct {
    ValueType type;
    union {
        int int_val;
        float float_val;
        char *str_val;
        int bool_val; // 0はfalse、1はtrueを表す
    };
} Value;

// キーの型の定義
typedef enum {
    KEY_INT,
    KEY_STRING
} KeyType;

typedef struct {
    KeyType type;
    union {
        int int_key;
        char *str_key;
    };
} Key;

// ノードの定義
typedef struct Node {
    Key key;               // キー
    Value value;           // 値
    struct Node *next;     // 次のノードへのポインタ（チェイン法用）
} Node;

// 関数の宣言
void insert(Key key, Value value);
Value *search(Key key);
void free_table();

#endif // HASH_TABLE_H