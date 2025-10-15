#ifndef HERB_LEXER_STRUCT_H
#define HERB_LEXER_STRUCT_H

#include "hb_arena.h"
#include "util/hb_string.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef enum {
  STATE_DATA,
  STATE_ERB_CONTENT,
  STATE_ERB_CLOSE,
} lexer_state_T;

typedef struct LEXER_STRUCT {
  hb_arena_T* allocator;
  hb_string_T source;

  uint32_t current_line;
  uint32_t current_column;
  uint32_t current_position;

  uint32_t previous_line;
  uint32_t previous_column;
  uint32_t previous_position;

  char current_character;
  lexer_state_T state;
  uint32_t stall_counter;
  uint32_t last_position;
  bool stalled;
} lexer_T;

#endif
