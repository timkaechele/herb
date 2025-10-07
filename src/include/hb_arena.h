#ifndef HERB_ARENA_H
#define HERB_ARENA_H

#include <stddef.h>

typedef struct HB_ARENA_ALLOCATOR_STRUCT hb_arena_allocator_T;

struct HB_ARENA_ALLOCATOR_STRUCT {
  char* memory;
  size_t capacity;
  size_t position;
};

void hb_arena_init(hb_arena_allocator_T* allocator, size_t size);
void* hb_arena_alloc(hb_arena_allocator_T* allocator, size_t size);
size_t hb_arena_pos(hb_arena_allocator_T* allocator);
void hb_arena_clear(hb_arena_allocator_T* allocator);
void hb_arena_reset_to(hb_arena_allocator_T* allocator, size_t new_position);
void hb_arena_free(hb_arena_allocator_T* allocator);

#endif
