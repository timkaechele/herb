#ifndef HERB_ARENA_H
#define HERB_ARENA_H

#include <stddef.h>

typedef struct HB_ARENA_ALLOCATOR_STRUCT hb_arena_allocator_T;


struct HB_ARENA_ALLOCATOR_STRUCT {
  char* buffer;
  size_t position;
  size_t capacity;
  hb_arena_allocator_T* next;
  hb_arena_allocator_T* temporary_arena;
};

void hb_arena_init(arena_allocator_T* allocator, size_t size);
void* hb_arena_alloc(arena_allocator_T* allocator, size_t size);
size_t hb_arena_pos(arena_allocator_T* allocator);
void hb_arena_clear(arena_allocator_T* allocator);

#endif
