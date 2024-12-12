#include "set.h"
#include <stdlib.h>
#include <string.h>

// ハッシュ関数
unsigned int hash(Data* key) {
    unsigned int hash_value = 0;
    switch (key->type) {
        case INT_TYPE:
            hash_value = key->data.int_value % TABLE_SIZE;
            break;
        case FLOAT_TYPE:
            hash_value = (unsigned int)(key->data.float_value) % TABLE_SIZE;
            break;
        case STRING_TYPE:
            for (char* p = key->data.string_value; *p != '\0'; p++) {
                hash_value = (hash_value * 31 + *p) % TABLE_SIZE;
            }
            break;
    }
    return hash_value;
}

// データの比較
int data_equals(Data* a, Data* b) {
    if (a->type != b->type) return 0;
    switch (a->type) {
        case INT_TYPE:
            return a->data.int_value == b->data.int_value;
        case FLOAT_TYPE:
            return a->data.float_value == b->data.float_value;
        case STRING_TYPE:
            return strcmp(a->data.string_value, b->data.string_value) == 0;
    }
    return 0;
}

// セットの初期化
void init_set(Set* set) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        set->table[i] = NULL;
    }
}

// 要素の追加
void add(Set* set, Data* value) {
    unsigned int index = hash(value);
    Node* node = set->table[index];
    while (node != NULL) {
        if (data_equals(&node->data, value)) {
            // 既に存在する場合は何もしない
            return;
        }
        node = node->next;
    }
    // 新しいノードを追加
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data.type = value->type;
    switch (value->type) {
        case INT_TYPE:
            new_node->data.data.int_value = value->data.int_value;
            break;
        case FLOAT_TYPE:
            new_node->data.data.float_value = value->data.float_value;
            break;
        case STRING_TYPE:
            new_node->data.data.string_value = strdup(value->data.string_value);
            break;
    }
    new_node->next = set->table[index];
    set->table[index] = new_node;
}

// 要素の存在確認
int contains(Set* set, Data* value) {
    unsigned int index = hash(value);
    Node* node = set->table[index];
    while (node != NULL) {
        if (data_equals(&node->data, value)) {
            return 1; // 存在する
        }
        node = node->next;
    }
    return 0; // 存在しない
}

// 要素の削除
void remove_element(Set* set, Data* value) {
    unsigned int index = hash(value);
    Node* node = set->table[index];
    Node* prev = NULL;
    while (node != NULL) {
        if (data_equals(&node->data, value)) {
            if (prev == NULL) {
                set->table[index] = node->next;
            } else {
                prev->next = node->next;
            }
            if (node->data.type == STRING_TYPE) {
                free(node->data.data.string_value);
            }
            free(node);
            return;
        }
        prev = node;
        node = node->next;
    }
}

// セットの解放
void free_set(Set* set) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* node = set->table[i];
        while (node != NULL) {
            Node* tmp = node;
            node = node->next;
            if (tmp->data.type == STRING_TYPE) {
                free(tmp->data.data.string_value);
            }
            free(tmp);
        }
        set->table[i] = NULL;
    }
}

// データの作成ヘルパー関数
Data create_int_data(int value) {
    Data data;
    data.type = INT_TYPE;
    data.data.int_value = value;
    return data;
}

Data create_float_data(float value) {
    Data data;
    data.type = FLOAT_TYPE;
    data.data.float_value = value;
    return data;
}

Data create_string_data(const char* value) {
    Data data;
    data.type = STRING_TYPE;
    data.data.string_value = strdup(value);
    return data;
}

// 集合演算の実装
Set set_union(Set* set1, Set* set2) {
    Set result;
    init_set(&result);

    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* node = set1->table[i];
        while (node != NULL) {
            add(&result, &node->data);
            node = node->next;
        }
        node = set2->table[i];
        while (node != NULL) {
            add(&result, &node->data);
            node = node->next;
        }
    }

    return result;
}

Set set_intersection(Set* set1, Set* set2) {
    Set result;
    init_set(&result);

    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* node = set1->table[i];
        while (node != NULL) {
            if (contains(set2, &node->data)) {
                add(&result, &node->data);
            }
            node = node->next;
        }
    }

    return result;
}

Set set_difference(Set* set1, Set* set2) {
    Set result;
    init_set(&result);

    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* node = set1->table[i];
        while (node != NULL) {
            if (!contains(set2, &node->data)) {
                add(&result, &node->data);
            }
            node = node->next;
        }
    }

    return result;
}

Set set_symmetric_difference(Set* set1, Set* set2) {
    Set result;
    init_set(&result);

    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* node = set1->table[i];
        while (node != NULL) {
            if (!contains(set2, &node->data)) {
                add(&result, &node->data);
            }
            node = node->next;
        }
        node = set2->table[i];
        while (node != NULL) {
            if (!contains(set1, &node->data)) {
                add(&result, &node->data);
            }
            node = node->next;
        }
    }

    return result;
}