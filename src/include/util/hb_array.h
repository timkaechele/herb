#ifndef HERB_NARRAY_H
#define HERB_NARRAY_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct HB_ARRAY_STRUCT {
  uint8_t* items;
  size_t item_size;
  size_t size;
  size_t capacity;
} hb_array_T;

void hb_array_init(hb_array_T* array, size_t item_size, size_t initial_capacity);
#define hb_array_pointer_init(array, initial_capacity) (hb_array_init(array, sizeof(void*), initial_capacity))

void* hb_array_get(const hb_array_T* array, size_t index);
void* hb_array_first(hb_array_T* array);
void* hb_array_last(hb_array_T* array);

void hb_array_append(hb_array_T* array, void* item);
void hb_array_remove(hb_array_T* array, size_t index);
void hb_array_deinit(hb_array_T* array);

#define hb_array_push(array, item) (hb_array_append((array), item))
bool hb_array_pop(hb_array_T* array, void* item);

#endif
