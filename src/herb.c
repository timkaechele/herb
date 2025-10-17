#include "include/herb.h"
#include "include/hb_arena.h"
#include "include/io.h"
#include "include/lexer.h"
#include "include/parser.h"
#include "include/token.h"
#include "include/util/hb_array.h"
#include "include/util/hb_buffer.h"
#include "include/version.h"

#include <prism.h>
#include <stdlib.h>

hb_array_T* herb_lex(const char* source) {
  hb_arena_T allocator;
  hb_arena_init(&allocator, MB(512));

  lexer_T lexer = { 0 };
  lexer_init(&lexer, &allocator, source);

  token_T* token = NULL;
  hb_array_T* tokens = hb_array_init(128);

  while ((token = lexer_next_token(&lexer))->type != TOKEN_EOF) {
    hb_array_append(tokens, token);
  }

  hb_array_append(tokens, token);

  return tokens;
}

AST_DOCUMENT_NODE_T* herb_parse(const char* source, parser_options_T* options) {
  if (!source) { source = ""; }

  hb_arena_T allocator;
  hb_arena_init(&allocator, MB(512));

  lexer_T lexer = { 0 };
  lexer_init(&lexer, &allocator, source);
  parser_T parser = { 0 };

  parser_options_T parser_options = HERB_DEFAULT_PARSER_OPTIONS;

  if (options != NULL) { parser_options = *options; }

  herb_parser_init(&allocator, &parser, &lexer, parser_options);

  AST_DOCUMENT_NODE_T* document = herb_parser_parse(&parser);

  return document;
}

hb_array_T* herb_lex_file(const char* path) {
  char* source = herb_read_file(path);
  hb_array_T* tokens = herb_lex(source);

  free(source);

  return tokens;
}

void herb_lex_to_buffer(const char* source, hb_buffer_T* output) {
  hb_array_T* tokens = herb_lex(source);

  for (size_t i = 0; i < hb_array_size(tokens); i++) {
    token_T* token = hb_array_get(tokens, i);

    char* type = token_to_string(token);
    hb_buffer_append(output, type);
    free(type);

    hb_buffer_append(output, "\n");
  }

  herb_free_tokens(&tokens);
}

void herb_free_tokens(hb_array_T** tokens) {
  if (!tokens || !*tokens) { return; }

  for (size_t i = 0; i < hb_array_size(*tokens); i++) {
    token_T* token = hb_array_get(*tokens, i);
    if (token) { token_free(token); }
  }

  hb_array_free(tokens);
}

const char* herb_version(void) {
  return HERB_VERSION;
}

const char* herb_prism_version(void) {
  return PRISM_VERSION;
}
