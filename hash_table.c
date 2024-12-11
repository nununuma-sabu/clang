#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100

// ノードの定義
typedef struct Node {
    char *key;             // キー
    int value;             // 値
    struct Node *next;     // 次のノードへのポインタ（チェイン法用）
} Node;

Node *hash_table[TABLE_SIZE];  // ハッシュテーブル

// ハッシュ関数の定義
unsigned int hash(char *key) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash << 5) + *key++;  // シンプルなハッシュ計算
    }
    return hash % TABLE_SIZE;
}

// キーと値を挿入する関数
void insert(char *key, int value) {
    unsigned int index = hash(key);
    Node *newnode = malloc(sizeof(Node));
    newnode->key = strdup(key);    // キーのコピーを保存
    newnode->value = value;
    newnode->next = hash_table[index];
    hash_table[index] = newnode;   // 新しいノードをハッシュテーブルに追加
}

// キーから値を検索する関数
int search(char *key) {
    unsigned int index = hash(key);
    Node *node = hash_table[index];
    while (node) {
        if (strcmp(node->key, key) == 0) {
            return node->value;    // キーが見つかった場合、値を返す
        }
        node = node->next;
    }
    return -1;  // キーが見つからなかった場合
}

// ハッシュテーブルのメモリを解放する関数
void free_table() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node *node = hash_table[i];
        while (node) {
            Node *temp = node;
            node = node->next;
            free(temp->key);       // キーのメモリを解放
            free(temp);            // ノードのメモリを解放
        }
    }
}

int main() {
    insert("apple", 100);
    insert("banana", 200);
    insert("orange", 300);

    printf("apple: %d\n", search("apple"));
    printf("banana: %d\n", search("banana"));
    printf("grape: %d\n", search("grape"));  // 存在しないキーの検索

    free_table();  // メモリの解放
    return 0;
}