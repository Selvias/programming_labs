#include "IntVector.h"

IntVector *int_vector_new(size_t init_capacity) {
    IntVector *vect = (IntVector*)malloc(sizeof(vect));
    vect->arr = (int*)malloc(init_capacity*sizeof(int));
    vect->size = 0;
    vect->capacity = init_capacity;
    if (vect != NULL)
        return vect;
    else
        return NULL;
}

IntVector *int_vector_copy(const IntVector *v) {
    IntVector *vect_copy = (IntVector*)v;
    if (vect_copy != NULL)
        return vect_copy;
    else    
        return NULL;
}

int int_vector_get_item(const IntVector *v, size_t index) {
    int item = v->arr[index];
    return item;
}

void int_vector_set_item(IntVector *v, size_t index, int item) {
    v->arr[index] = item;
    v->size += 1;
}

size_t int_vector_get_size(const IntVector *v) {
    return v->size;
}

size_t int_vector_get_capacity(const IntVector *v) {
    return v->capacity;
}

int int_vector_push_back(IntVector *v, int item) {                //Добавление элемента в конец массива

    if (v->capacity == 0) {
        printf("ADDITION FAILED\n");
        exit(-1);
    } else if (v->size < v->capacity)
    {
        v->arr[v->size] = item;
        ++(v->size);
        return 0;
    } else if (v->size >= v->capacity) {                        // >= потому, что индексация начинается с нуля, и фактически по адресу == capacity элемента нет.
        int_vector_reserve(v, 2*(v->capacity));
        int_vector_push_back(v, item);
    }

    return 0;
}

void int_vector_pop_back(IntVector *v) {
    if (v->size != 0) 
    {
        //delete
        (v->size)--;
    }

}

int int_vector_shrink_to_fit(IntVector *v) {
    if (v != NULL && v->capacity != 0)
    {
        v->arr = (int*)realloc(v->arr, v->size*sizeof(int));
        v->capacity = v->size;
        return 0; 

    } else
        return -1;
}

int int_vector_resize(IntVector *v, size_t new_size) {

    if (new_size > v->size && new_size > v->capacity) {
        size_t temp_size = v->size;
        int_vector_reserve(v, 2*(new_size));
        for (int i = temp_size; i < new_size; i++)
        {
            v->arr[i] = 0;
        }
        return 0;
    } else if (new_size < v->size) {
        v->size = new_size;
        int_vector_shrink_to_fit(v);
        // int_vector_reserve(v, new_size);
        return 0;
    } else if (new_size > v->size && new_size < v->capacity) {
        size_t temp_size = v->size;
        int_vector_reserve(v, 2*(new_size));
        for (int i = temp_size; i < new_size; i++)
        {
            v->arr[i] = 0;
        }
        return 0;
    } else
        return -1;
}

int int_vector_reserve(IntVector *v, size_t new_capacity) {
    
    if (new_capacity > v->capacity)
    {
        v->arr = (int*) realloc(v->arr, new_capacity*sizeof(int));
        v->capacity = new_capacity;
        return 0;
    } else 
        return -1;
}

void int_vector_free(IntVector *v) {
    free(v->arr);
    v->size = v->capacity = 0;
}