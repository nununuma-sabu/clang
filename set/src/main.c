#include "set.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    Set set1, set2;
    init_set(&set1);
    init_set(&set2);

    Data data1 = create_int_data(10);
    Data data2 = create_float_data(3.14f);
    Data data3 = create_string_data("hello");
    Data data4 = create_int_data(20);
    Data data5 = create_float_data(2.71f);
    Data data6 = create_string_data("world");

    add(&set1, &data1);
    add(&set1, &data2);
    add(&set1, &data3);

    add(&set2, &data3);
    add(&set2, &data4);
    add(&set2, &data5);
    add(&set2, &data6);

    Set union_set = set_union(&set1, &set2);
    Set intersection_set = set_intersection(&set1, &set2);
    Set difference_set = set_difference(&set1, &set2);
    Set symmetric_difference_set = set_symmetric_difference(&set1, &set2);

    // 結果の表示
    printf("Union set:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* node = union_set.table[i];
        while (node != NULL) {
            if (node->data.type == INT_TYPE) {
                printf("%d ", node->data.data.int_value);
            } else if (node->data.type == FLOAT_TYPE) {
                printf("%f ", node->data.data.float_value);
            } else if (node->data.type == STRING_TYPE) {
                printf("%s ", node->data.data.string_value);
            }
            node = node->next;
        }
    }
    printf("\n");

    printf("Intersection set:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* node = intersection_set.table[i];
        while (node != NULL) {
            if (node->data.type == INT_TYPE) {
                printf("%d ", node->data.data.int_value);
            } else if (node->data.type == FLOAT_TYPE) {
                printf("%f ", node->data.data.float_value);
            } else if (node->data.type == STRING_TYPE) {
                printf("%s ", node->data.data.string_value);
            }
            node = node->next;
        }
    }
    printf("\n");

    printf("Difference set:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* node = difference_set.table[i];
        while (node != NULL) {
            if (node->data.type == INT_TYPE) {
                printf("%d ", node->data.data.int_value);
            } else if (node->data.type == FLOAT_TYPE) {
                printf("%f ", node->data.data.float_value);
            } else if (node->data.type == STRING_TYPE) {
                printf("%s ", node->data.data.string_value);
            }
            node = node->next;
        }
    }
    printf("\n");

    printf("Symmetric Difference set:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* node = symmetric_difference_set.table[i];
        while (node != NULL) {
            if (node->data.type == INT_TYPE) {
                printf("%d ", node->data.data.int_value);
            } else if (node->data.type == FLOAT_TYPE) {
                printf("%f ", node->data.data.float_value);
            } else if (node->data.type == STRING_TYPE) {
                printf("%s ", node->data.data.string_value);
            }
            node = node->next;
        }
    }
    printf("\n");

    // メモリの解放
    free_set(&set1);
    free_set(&set2);
    free_set(&union_set);
    free_set(&intersection_set);
    free_set(&difference_set);
    free_set(&symmetric_difference_set);

    // ヘルパー関数で作成した文字列を解放
    free(data3.data.string_value);
    free(data6.data.string_value);

    return 0;
}