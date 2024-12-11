#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

Node *hash_table[TABLE_SIZE];  // ハッシュテーブル

// ハッシュ関数の定義
unsigned int hash(Key key) {
    unsigned int hash = 0;
    if (key.type == KEY_STRING) {
        char *str = key.str_key;
        while (*str) {
            hash = (hash << 5) + *str++;
        }
    } else if (key.type == KEY_INT) {
        hash = key.int_key;
    }
    return hash % TABLE_SIZE;
}

// キーと値を挿入する関数
void insert(Key key, Value value) {
    unsigned int index = hash(key);
    Node *newnode = malloc(sizeof(Node));
    newnode->key = key;
    if (key.type == KEY_STRING) {
        newnode->key.str_key = strdup(key.str_key);
    }
    newnode->value = value;
    if (value.type == TYPE_STRING) {
        newnode->value.str_val = strdup(value.str_val);
    }
    newnode->next = hash_table[index];
    hash_table[index] = newnode;
}

// キーから値を検索する関数
Value *search(Key key) {
    unsigned int index = hash(key);
    Node *node = hash_table[index];
    while (node) {
        int match = 0;
        if (key.type == node->key.type) {
            if (key.type == KEY_STRING) {
                if (strcmp(key.str_key, node->key.str_key) == 0) {
                    match = 1;
                }
            } else if (key.type == KEY_INT) {
                if (key.int_key == node->key.int_key) {
                    match = 1;
                }
            }
            if (match) {
                return &node->value;
            }
        }
        node = node->next;
    }
    return NULL;  // キーが見つからなかった場合
}

// ハッシュテーブルのメモリを解放する関数
void free_table() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node *node = hash_table[i];
        while (node) {
            Node *temp = node;
            node = node->next;
            if (temp->key.type == KEY_STRING) {
                free(temp->key.str_key);
            }
            if (temp->value.type == TYPE_STRING) {
                free(temp->value.str_val);
            }
            free(temp);
        }
    }
}

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