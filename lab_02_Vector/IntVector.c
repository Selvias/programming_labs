#include "IntVector.h"

IntVector *int_vector_new(size_t init_capacity) {
  IntVector *vect = (IntVector *)malloc(sizeof(IntVector));
  if (vect == NULL)
    return NULL;
  vect->arr = (int *)malloc(init_capacity * sizeof(int));
  if (vect->arr == NULL) {
    free(vect);
    return NULL;
  }
  vect->size = 0;
  vect->capacity = init_capacity;

  return vect;
}

IntVector *int_vector_copy(const IntVector *v) {
  if (v != NULL) {
    IntVector *vect_copy = NULL;
    vect_copy = int_vector_new(v->capacity);
    if (vect_copy == NULL)
      return NULL;
    vect_copy->capacity = v->capacity;
    vect_copy->size = v->size;

    for (int j = 0; j < v->size; j++) {
      vect_copy->arr[j] = v->arr[j];
    }

    return vect_copy;
  } else
    return NULL;
}

int int_vector_get_item(const IntVector *v, size_t index) {
  if ((v != NULL) && (index < v->size)) {
    int item = v->arr[index];
    return item;
  } else
    return -1;
}

void int_vector_set_item(IntVector *v, size_t index, int item) {
  if (v != NULL && index < v->size)
    v->arr[index] = item;
}

size_t int_vector_get_size(const IntVector *v) {
  if (v == NULL)
    return -1;
  
  return v->size;
}

size_t int_vector_get_capacity(const IntVector *v) { 
  if (v == NULL)
    return -1;

  return v->capacity; 
}

int int_vector_push_back(IntVector *v, int item) {

  short int flag = 0;

  if (v->capacity == 0) {
    printf("ADDITION FAILED\n");
    return -1;
  } else if (v->size < v->capacity) {
    v->arr[v->size] = item;
    ++(v->size);
    return 0;
  } else if (v->size >= v->capacity) {
    flag = int_vector_reserve(v, 2 * (v->capacity));
    if (flag == -1)
      return -1;
    int_vector_push_back(v, item);
    return 0;
  } else
    return -1;
}

void int_vector_pop_back(IntVector *v) {
  if ((v != NULL) && (v->size != 0) && (v->capacity != 0)) {
    v->arr[v->size - 1] = 0;
    (v->size)--;
  }
}

int int_vector_shrink_to_fit(IntVector *v) {
  if (v != NULL && v->capacity != 0 && v->size != 0) {
    v->arr = (int *)realloc(v->arr, v->size * sizeof(int));
    if (v->arr == NULL)
      return -1;
    v->capacity = v->size;
    return 0;
  } else
    return -1;
}

int int_vector_resize(IntVector *v, size_t new_size) {

  short int flag = 0;

  if (v == NULL)
    return -1;

  if (new_size > v->size && new_size > v->capacity) {
    size_t temp_size = v->size;
    flag = int_vector_reserve(v, 2 * (new_size));
    if (flag == -1)
      return flag;
    for (int i = temp_size; i < new_size; i++) {
      v->arr[i] = 0;
    }
    v->size = new_size;
    return 0;
  } else if (new_size < v->size && new_size != 0) {
    v->size = new_size;
    flag = int_vector_shrink_to_fit(v);
    if (flag == -1)
      return flag;
    return 0;
  } else if (new_size < v->size && new_size == 0) {
    v->size = new_size;
    return 0;
  } else if (new_size > v->size && new_size <= v->capacity) {
    size_t temp_size = v->size;
    for (int i = temp_size; i < new_size; i++) {
      v->arr[i] = 0;
    }
    v->size = new_size;
    return 0;
  } else
    return -1;
}

int int_vector_reserve(IntVector *v, size_t new_capacity) {

  int *check = NULL;

  if (v != NULL && new_capacity > v->capacity && new_capacity > 0) {
    
    check = (int *)realloc(v->arr, new_capacity * sizeof(int));

    if (check != NULL)
      v->arr = check;
    
    if (v->arr == NULL)
      return -1;
    v->capacity = new_capacity;
    return 0;
  } else
    return -1;
}

void int_vector_free(IntVector *v) {
  free(v->arr);
  free(v);
}