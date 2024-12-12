#include "set.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    Set mySet;
    init_set(&mySet);

    Data data1 = create_int_data(10);
    Data data2 = create_float_data(3.14f);
    Data data3 = create_string_data("hello");

    add(&mySet, &data1);
    add(&mySet, &data2);
    add(&mySet, &data3);

    if (contains(&mySet, &data1)) {
        printf("10 is in the set.\n");
    }

    if (contains(&mySet, &data2)) {
        printf("3.14 is in the set.\n");
    }

    if (contains(&mySet, &data3)) {
        printf("\"hello\" is in the set.\n");
    }

    remove_element(&mySet, &data1);

    if (!contains(&mySet, &data1)) {
        printf("10 has been removed from the set.\n");
    }

    // ヘルパー関数で作成した文字列を解放
    free(data3.data.string_value);

    free_set(&mySet);

    return 0;
}