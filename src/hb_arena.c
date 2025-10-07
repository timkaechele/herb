#include "include/memory_arena.h"

#include <stdlib.h>

void hb_arena_init(arena_allocator_T *allocator, size_t size) {
  allocator->buffer = NULL;
  allocator->position = 0;
  allocator->capacity = size;
}

void* hb_arena_alloc(arena_allocator_T* allocator, size_t size) {
  // TODO: Alignment
  // void *ptr = &allocator->buffer[allocator->position];

  // allocator->position += size;

  // return ptr;
  return malloc(size);
}

size_t arena_pos(arena_allocator_T* allocator) {
  return allocator->position;
}

void arena_clear(arena_allocator_T* allocator) {
  allocator->position = 0;
}
