#include "IntVector.h"

int main() {

    static size_t /*index, size, capacity,*/ init_capacity = 10;
    // int item = 4;

    IntVector *v = NULL;
    // IntVector *v_copy = NULL;

    v = int_vector_new(init_capacity);

    for (int i = 0; i < 11; i++)
    {
        int_vector_push_back(v, i);
    }

    printf("VECTOR_FILLING : ");

    for (int i = 0; i < 11; i++)
    {
        printf("%d",v->arr[i]);
        printf(" ");
    }

    printf("\nSIZE_VECTOR : %d\nCAPACITY_VECTOR : %d\n", v->size, v->capacity);

    v = int_vector_new(init_capacity);

    int_vector_free(v);

    printf("\nSIZE_VECTOR : %d\nCAPACITY_VECTOR : %d\n", v->size, v->capacity);

    int_vector_push_back(v, 24);
    
    int_vector_resize(v, 15);

    int_vector_push_back(v, 24);

    printf("\nSIZE_VECTOR : %d\nCAPACITY_VECTOR : %d\n", v->size, v->capacity);

    return 0;
}