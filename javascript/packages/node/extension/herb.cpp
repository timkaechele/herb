extern "C" {
#include "../extension/libherb/include/analyze.h"
#include "../extension/libherb/include/array.h"
#include "../extension/libherb/include/ast_nodes.h"
#include "../extension/libherb/include/buffer.h"
#include "../extension/libherb/include/herb.h"
#include "../extension/libherb/include/location.h"
#include "../extension/libherb/include/range.h"
#include "../extension/libherb/include/token.h"
}

#include "error_helpers.h"
#include "extension_helpers.h"
#include "nodes.h"

#include <node_api.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

napi_value Herb_lex(napi_env env, napi_callback_info info) {
  size_t argc = 1;
  napi_value args[1];
  napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

  if (argc < 1) {
    napi_throw_error(env, nullptr, "Wrong number of arguments");
    return nullptr;
  }

  char* string = CheckString(env, args[0]);
  if (!string) { return nullptr; }

  array_T* tokens = herb_lex(string);
  napi_value result = CreateLexResult(env, tokens, args[0]);

  herb_free_tokens(&tokens);
  free(string);

  return result;
}

napi_value Herb_lex_file(napi_env env, napi_callback_info info) {
  size_t argc = 1;
  napi_value args[1];
  napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

  if (argc < 1) {
    napi_throw_error(env, nullptr, "Wrong number of arguments");
    return nullptr;
  }

  char* file_path = CheckString(env, args[0]);
  if (!file_path) { return nullptr; }

  array_T* tokens = herb_lex_file(file_path);
  napi_value source_value = ReadFileToString(env, file_path);
  napi_value result = CreateLexResult(env, tokens, source_value);

  herb_free_tokens(&tokens);
  free(file_path);

  return result;
}

napi_value Herb_parse(napi_env env, napi_callback_info info) {
  size_t argc = 2;
  napi_value args[2];
  napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

  if (argc < 1) {
    napi_throw_error(env, nullptr, "Wrong number of arguments");
    return nullptr;
  }

  char* string = CheckString(env, args[0]);
  if (!string) { return nullptr; }

  parser_options_T* parser_options = nullptr;
  parser_options_T opts = {0};

  if (argc >= 2) {
    napi_valuetype valuetype;
    napi_typeof(env, args[1], &valuetype);

    if (valuetype == napi_object) {
      napi_value track_whitespace_prop;
      bool has_prop;
      napi_has_named_property(env, args[1], "track_whitespace", &has_prop);

      if (has_prop) {
        napi_get_named_property(env, args[1], "track_whitespace", &track_whitespace_prop);
        bool track_whitespace_value;
        napi_get_value_bool(env, track_whitespace_prop, &track_whitespace_value);

        if (track_whitespace_value) {
          opts.track_whitespace = true;
          parser_options = &opts;
        }
      }
    }
  }

  AST_DOCUMENT_NODE_T* root = herb_parse(string, parser_options);
  herb_analyze_parse_tree(root, string);
  napi_value result = CreateParseResult(env, root, args[0]);

  ast_node_free((AST_NODE_T *) root);
  free(string);

  return result;
}

napi_value Herb_parse_file(napi_env env, napi_callback_info info) {
  size_t argc = 1;
  napi_value args[1];
  napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

  if (argc < 1) {
    napi_throw_error(env, nullptr, "Wrong number of arguments");
    return nullptr;
  }

  char* file_path = CheckString(env, args[0]);
  if (!file_path) { return nullptr; }

  napi_value source_value = ReadFileToString(env, file_path);

  char* string = CheckString(env, source_value);
  if (!string) {
    free(file_path);
    return nullptr;
  }

  AST_DOCUMENT_NODE_T* root = herb_parse(string, nullptr);
  napi_value result = CreateParseResult(env, root, source_value);

  ast_node_free((AST_NODE_T *) root);
  free(file_path);
  free(string);

  return result;
}

napi_value Herb_extract_ruby(napi_env env, napi_callback_info info) {
  size_t argc = 1;
  napi_value args[1];
  napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

  if (argc < 1) {
    napi_throw_error(env, nullptr, "Wrong number of arguments");
    return nullptr;
  }

  char* string = CheckString(env, args[0]);
  if (!string) { return nullptr; }

  buffer_T output;
  if (!buffer_init(hb_arena_global(), &output, strlen(string))) {
    free(string);
    napi_throw_error(env, nullptr, "Failed to initialize buffer");
    return nullptr;
  }

  herb_extract_ruby_to_buffer(string, &output);

  napi_value result;
  napi_create_string_utf8(env, output.value, NAPI_AUTO_LENGTH, &result);

  free(output.value);
  free(string);
  return result;
}

napi_value Herb_extract_html(napi_env env, napi_callback_info info) {
  size_t argc = 1;
  napi_value args[1];
  napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

  if (argc < 1) {
    napi_throw_error(env, nullptr, "Wrong number of arguments");
    return nullptr;
  }

  char* string = CheckString(env, args[0]);
  if (!string) { return nullptr; }

  buffer_T output;
  if (!buffer_init(hb_arena_global(), &output, strlen(string))) {
    free(string);
    napi_throw_error(env, nullptr, "Failed to initialize buffer");
    return nullptr;
  }

  herb_extract_html_to_buffer(string, &output);

  napi_value result;
  napi_create_string_utf8(env, output.value, NAPI_AUTO_LENGTH, &result);

  free(output.value);
  free(string);
  return result;
}

napi_value Herb_version(napi_env env, napi_callback_info info) {
  const char* libherb_version = herb_version();
  const char* libprism_version = herb_prism_version();

  char version_buf[256];
  snprintf(version_buf, sizeof(version_buf), "libprism@%s, libherb@%s (Node.js C++ native extension)", libprism_version, libherb_version);

  napi_value result;
  napi_create_string_utf8(env, version_buf, NAPI_AUTO_LENGTH, &result);

  return result;
}

napi_value Init(napi_env env, napi_value exports) {
  napi_property_descriptor descriptors[] = {
    { "parse", nullptr, Herb_parse, nullptr, nullptr, nullptr, napi_default, nullptr },
    { "lex", nullptr, Herb_lex, nullptr, nullptr, nullptr, napi_default, nullptr },
    { "parseFile", nullptr, Herb_parse_file, nullptr, nullptr, nullptr, napi_default, nullptr },
    { "lexFile", nullptr, Herb_lex_file, nullptr, nullptr, nullptr, napi_default, nullptr },
    { "extractRuby", nullptr, Herb_extract_ruby, nullptr, nullptr, nullptr, napi_default, nullptr },
    { "extractHTML", nullptr, Herb_extract_html, nullptr, nullptr, nullptr, napi_default, nullptr },
    { "version", nullptr, Herb_version, nullptr, nullptr, nullptr, napi_default, nullptr },
  };

  napi_define_properties(env, exports, sizeof(descriptors) / sizeof(descriptors[0]), descriptors);

  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
