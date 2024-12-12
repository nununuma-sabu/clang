#ifndef SET_H
#define SET_H

#include <stdio.h>

#define TABLE_SIZE 100

typedef enum {
    INT_TYPE,
    FLOAT_TYPE,
    STRING_TYPE
} DataType;

typedef struct {
    DataType type;
    union {
        int int_value;
        float float_value;
        char* string_value;
    } data;
} Data;

typedef struct Node {
    Data data;
    struct Node* next;
} Node;

typedef struct Set {
    Node* table[TABLE_SIZE];
} Set;

// 関数の宣言
unsigned int hash(Data* key);
int data_equals(Data* a, Data* b);
void init_set(Set* set);
void add(Set* set, Data* value);
int contains(Set* set, Data* value);
void remove_element(Set* set, Data* value);
void free_set(Set* set);
Data create_int_data(int value);
Data create_float_data(float value);
Data create_string_data(const char* value);

#endif // SET_H