#define _POSIX_C_SOURCE 199309L // Enables `clock_gettime()`

#include "include/analyze.h"
#include "include/ast_node.h"
#include "include/ast_nodes.h"
#include "include/ast_pretty_print.h"
#include "include/buffer.h"
#include "include/extract.h"
#include "include/herb.h"
#include "include/io.h"
#include "include/ruby_parser.h"

#include <stdio.h>
#include <string.h>
#include <time.h>

void print_time_diff(const struct timespec start, const struct timespec end, const char* verb) {
  const double seconds = (double) end.tv_sec - (double) start.tv_sec;
  const double nanoseconds = (double) end.tv_nsec - (double) start.tv_nsec;
  const double total_ns = seconds * 1e9 + nanoseconds;

  const double us = total_ns / 1e3;
  const double ms = total_ns / 1e6;
  const double s = total_ns / 1e9;

  printf("Finished");
  printf(" %s ", verb);
  printf("in:\n\n");

  printf("  %8.0f µs\n", us);
  printf("  %8.3f ms\n", ms);
  printf("  %8.6f  s\n\n", s);
}

int main(const int argc, char* argv[]) {
  if (argc < 2) {
    printf("./herb [command] [options]\n\n");

    printf("Herb 🌿 Powerful and seamless HTML-aware ERB parsing and tooling.\n\n");

    printf("./herb lex [file]      -  Lex a file\n");
    printf("./herb parse [file]    -  Parse a file\n");
    printf("./herb ruby [file]     -  Extract Ruby from a file\n");
    printf("./herb html [file]     -  Extract HTML from a file\n");
    printf("./herb prism [file]    -  Extract Ruby from a file and parse the Ruby source with Prism\n");

    return 1;
  }

  if (argc < 3) {
    printf("Please specify input file.\n");
    return 1;
  }

  buffer_T output;

  if (!buffer_init(hb_arena_global(), &output, 4096)) { return 1; }

  char* source = herb_read_file(argv[2]);

  struct timespec start, end;
  clock_gettime(CLOCK_MONOTONIC, &start);

  if (strcmp(argv[1], "visit") == 0) {
    AST_DOCUMENT_NODE_T* root = herb_parse(source, NULL);
    clock_gettime(CLOCK_MONOTONIC, &end);

    herb_analyze_parse_tree(root, source);

    ast_pretty_print_node((AST_NODE_T*) root, 0, 0, &output);
    printf("%s\n", output.value);

    print_time_diff(start, end, "visiting");

    ast_node_free((AST_NODE_T*) root);

    return 0;
  }

  if (strcmp(argv[1], "lex") == 0) {
    herb_lex_to_buffer(source, &output);
    clock_gettime(CLOCK_MONOTONIC, &end);

    printf("%s\n", output.value);
    print_time_diff(start, end, "lexing");

    return 0;
  }

  if (strcmp(argv[1], "parse") == 0) {
    AST_DOCUMENT_NODE_T* root = herb_parse(source, NULL);

    herb_analyze_parse_tree(root, source);

    clock_gettime(CLOCK_MONOTONIC, &end);

    int silent = 0;
    if (argc > 3 && strcmp(argv[3], "--silent") == 0) { silent = 1; }

    if (!silent) {
      ast_pretty_print_node((AST_NODE_T*) root, 0, 0, &output);
      printf("%s\n", output.value);

      print_time_diff(start, end, "parsing");
    }

    ast_node_free((AST_NODE_T*) root);

    return 0;
  }

  if (strcmp(argv[1], "ruby") == 0) {
    herb_extract_ruby_to_buffer(source, &output);
    clock_gettime(CLOCK_MONOTONIC, &end);

    printf("%s\n", output.value);
    print_time_diff(start, end, "extracting Ruby");

    return 0;
  }

  if (strcmp(argv[1], "html") == 0) {
    herb_extract_html_to_buffer(source, &output);
    clock_gettime(CLOCK_MONOTONIC, &end);

    printf("%s\n", output.value);
    print_time_diff(start, end, "extracting HTML");

    return 0;
  }

  if (strcmp(argv[1], "prism") == 0) {
    printf("HTML+ERB File: \n%s\n", source);

    char* ruby_source = herb_extract(source, HERB_EXTRACT_LANGUAGE_RUBY);
    printf("Extracted Ruby: \n%s\n", ruby_source);

    herb_parse_ruby_to_stdout(ruby_source);

    return 0;
  }

  printf("Unknown Command: %s\n", argv[1]);
  return 1;
}
