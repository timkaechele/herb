#ifndef HERB_H
#define HERB_H

#include "array.h"
#include "ast_node.h"
#include "buffer.h"
#include "extract.h"

#include <stdint.h>

void herb_lex_to_buffer(char* source, buffer_T* output);
void herb_lex_json_to_buffer(char* source, buffer_T* output);
array_T* herb_lex(char* source);
array_T* herb_lex_file(const char* path);
AST_DOCUMENT_NODE_T* herb_parse(char* source);
const char* herb_version(void);
void herb_free_tokens(array_T** tokens);

#endif
