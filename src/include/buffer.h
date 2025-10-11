#ifndef HERB_BUFFER_H
#define HERB_BUFFER_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct BUFFER_STRUCT {
  char* value;
  size_t length;
  size_t capacity;
} buffer_T;

bool buffer_init(buffer_T* buffer, size_t capacity);

bool buffer_has_capacity(buffer_T* buffer, size_t required_length);
bool buffer_expand_if_needed(buffer_T* buffer, size_t required_length);
bool buffer_resize(buffer_T* buffer, size_t new_capacity);

void buffer_append(buffer_T* buffer, const char* text);
void buffer_append_with_length(buffer_T* buffer, const char* text, size_t length);
void buffer_append_char(buffer_T* buffer, char character);
void buffer_append_repeated(buffer_T* buffer, char character, size_t length);
void buffer_append_whitespace(buffer_T* buffer, size_t length);

char* buffer_value(const buffer_T* buffer);

size_t buffer_length(const buffer_T* buffer);
size_t buffer_capacity(const buffer_T* buffer);
size_t buffer_sizeof(void);

void buffer_clear(buffer_T* buffer);
void buffer_free(buffer_T** buffer);

#endif
