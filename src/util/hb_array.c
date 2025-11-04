#include "../include/util/hb_array.h"

#include <assert.h>
#include <stdbool.h>
#include <string.h>

void hb_array_init(hb_array_T* array, size_t item_size, size_t initial_capacity) {
  assert(initial_capacity != 0);

  array->item_size = item_size;
  array->capacity = initial_capacity;
  array->size = 0;
  array->items = malloc(array->capacity * array->item_size);
}

void hb_array_append(hb_array_T* array, void* item) {
  if (array->size + 1 > array->capacity) {
    array->capacity *= 2;
    void* new_buffer = realloc(array->items, array->capacity * array->item_size);
    assert(new_buffer != NULL);
    array->items = new_buffer;
  }

  memcpy(array->items + (array->size * array->item_size), item, array->item_size);
  array->size += 1;
}

static inline uint8_t* hb_array_memory_position(const hb_array_T* array, size_t index) {
  return array->items + (array->item_size * index);
}

void hb_array_remove(hb_array_T* array, size_t index) {
  assert(index < array->size);

  if (array->size - 1 > index) {
    size_t elements_to_shift = (array->size - 1) - index;
    size_t bytes_to_shift = array->item_size * elements_to_shift;

    memcpy(hb_array_memory_position(array, index), hb_array_memory_position(array, index + 1), bytes_to_shift);
  }

  array->size -= 1;
}

void* hb_array_get(const hb_array_T* array, size_t index) {
  assert(index < array->size);

  return hb_array_memory_position(array, index);
}

void* hb_array_first(hb_array_T* array) {
  if (array->size == 0) { return NULL; }

  return hb_array_get(array, 0);
}

void* hb_array_last(hb_array_T* array) {
  if (array->size == 0) { return NULL; }
  return hb_array_get(array, array->size - 1);
}

bool hb_array_pop(hb_array_T* array, void* item) {
  if (array->size == 0) { return false; }
  memcpy(item, hb_array_last(array), array->item_size);
  array->size -= 1;

  return true;
}

void hb_array_deinit(hb_array_T* array) {
  array->item_size = 0;
  array->capacity = 0;
  array->size = 0;
  if (array->items != NULL) {
    free(array->items);
    array->items = NULL;
  }
}
