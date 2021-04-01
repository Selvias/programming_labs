#include "IntVector.h"

int main() {

  static int g_item, s_item = 25, g_size, g_capacity;
  static size_t init_capacity = 10;

  IntVector *v = NULL;
  IntVector *v_copy = NULL;

  // 1. Создание нового вектора.
  v = int_vector_new(init_capacity);

  // 2.Добавление элементов в конец массива.
  if (v != NULL) {
    for (int i = 0; i < 11; i++) {
      int_vector_push_back(v, i);
    }
  }

  // 3.Копия вектора
  if (v != NULL) {
    v_copy = int_vector_copy(v);
  }
  // 4.Получение элемента по индексу
  if (v != NULL) {
    g_item = int_vector_get_item(v, 10);
  }

  // 5.Установление значения по индексу
  if (v != NULL) {
    int_vector_set_item(v, 5, s_item);
  }

  // 6.Получение размера
  if (v != NULL) {
    g_size = int_vector_get_size(v);
  }
  // 7.Получение ёмкости
  if (v != NULL) {
    g_capacity = int_vector_get_capacity(v);
  }

  printf("G_ITEM : %d\nCHECK_SET_ITEM : %d\nG_SIZE : %d\nG_CAPACITY : %d\n",
         g_item, v->arr[5], g_size, g_capacity);

  printf("VECTOR_FILLING : ");
  if (v != NULL) {
    for (int i = 0; i < 11; i++) {
      printf("%d", v->arr[i]);
      printf(" ");
    }
  }

  // 8. Добавление элемента в конец массива
  if (v != NULL) {
    int_vector_push_back(v, 24);
  }
  // 9. Изменение размера массива
  if (v != NULL) {
    int_vector_resize(v, 9);
  }
  // 10. Удаление последнего элемента массива
  if (v != NULL) {
    int_vector_pop_back(v);
  }

  // 10.1. Изменение размера массива (граничный случай)
  if (v != NULL) {
    int_vector_resize(v, 0);
  }

    printf("CAP_TEST : %d\n", v->capacity);

  // 10.2. Добавление элемента в конец массива
  if (v != NULL) {
    int_vector_push_back(v, 25);
  }

  printf("\nSIZE_VECTOR : %d\nCAPACITY_VECTOR : %d\n", v->size, v->capacity);

  // 11. Освобождение памяти из под вектора
  if (v != NULL && v_copy != NULL) {
    int_vector_free(v);
    int_vector_free(v_copy);
  }

  return 0;
}