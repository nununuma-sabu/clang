#include "hash_table.h"
#include <stdlib.h>
#include <string.h>

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