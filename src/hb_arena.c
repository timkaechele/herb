#ifdef __linux__
#define _GNU_SOURCE
#endif
#include "include/hb_arena.h"
#include <sys/mman.h>

#define KB(kb) (1024 * kb)
#define MB(mb) (1024 * KB(mb))

void hb_arena_init(hb_arena_allocator_T* allocator, size_t size) {
  allocator->memory = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  allocator->position = 0;
  allocator->capacity = size;
}

void* hb_arena_alloc(hb_arena_allocator_T* allocator, size_t size) {
  size_t required_size = ((size + 7) / 8) * 8; // rounds up to the next 8 bytes

  if (allocator->position + required_size > allocator->capacity) { return NULL; }

  size_t offset = allocator->position;
  void* ptr = &allocator->memory[offset];
  allocator->position += required_size;

  return ptr;
}

size_t hb_arena_pos(hb_arena_allocator_T* allocator) {
  return allocator->position;
}

void hb_arena_reset(hb_arena_allocator_T* allocator) {
  allocator->position = 0;
}

void hb_arena_reset_to(hb_arena_allocator_T* allocator, size_t new_position) {
  allocator->position = new_position;
}

void hb_arena_free(hb_arena_allocator_T* allocator) {
  if (allocator->memory != NULL) {
    munmap(allocator->memory, allocator->capacity);
    allocator->memory = NULL;
    allocator->position = 0;
    allocator->capacity = 0;
  }
}
