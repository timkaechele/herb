#ifndef HERB_EXTRACT_H
#define HERB_EXTRACT_H

#include "util/hb_arena.h"
#include "util/hb_buffer.h"

typedef enum {
  HERB_EXTRACT_LANGUAGE_RUBY,
  HERB_EXTRACT_LANGUAGE_HTML,
} herb_extract_language_T;

void herb_extract_ruby_to_buffer(hb_arena_T* allocator, const char* source, hb_buffer_T* output);
void herb_extract_html_to_buffer(hb_arena_T* allocator, const char* source, hb_buffer_T* output);

char* herb_extract_ruby_with_semicolons(hb_arena_T* allocator, const char* source);
void herb_extract_ruby_to_buffer_with_semicolons(hb_arena_T* allocator, const char* source, hb_buffer_T* output);

char* herb_extract(hb_arena_T* allocator, const char* source, herb_extract_language_T language);
char* herb_extract_from_file(hb_arena_T* allocator, const char* path, herb_extract_language_T language);

#endif
