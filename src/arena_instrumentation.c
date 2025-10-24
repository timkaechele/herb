#include "include/util/hb_system.h"
#include "include/util/hb_arena.h"
#include "include/util/hb_arena_instrumentation.h"

#include "util/hb_system.c"
#include "util/hb_arena.c"
#include "util/hb_arena_instrumentation.c"
#include <stdio.h>

int main() {
  hb_arena_T arena;

  hb_arena_init(&arena, 1024);

  for (int i = 0; i < 200; ++i)
  {
    hb_arena_alloc(&arena, i + 1);
  }

  hb_arena_reset_to(&arena, 0);

  hb_arena_free(&arena);
}
