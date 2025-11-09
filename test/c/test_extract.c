#include "include/test.h"

#include "../../src/include/herb.h"
#include "../../src/include/extract.h"
#include "../../src/include/util/hb_buffer.h"
#include "../../src/include/macros.h"

TEST(extract_ruby_single_erb_no_semicolon)
  hb_arena_T allocator;
  hb_arena_init(&allocator, MB(1));

  char* source = "<% if %>\n<% end %>";
  char* result = herb_extract_ruby_with_semicolons(&allocator, source);

  char expected[] = "   if   \n   end   ";
  ck_assert_str_eq(result, expected);

  free(result);
  hb_arena_free(&allocator);
END

TEST(extract_ruby_multiple_erb_same_line_with_semicolon)
  hb_arena_T allocator;
  hb_arena_init(&allocator, MB(1));

  char* source = "<% x = 1 %> <% y = 2 %>";
  char* result = herb_extract_ruby_with_semicolons(&allocator, source);

  ck_assert_str_eq(result, "   x = 1  ;    y = 2   ");

  free(result);
  hb_arena_free(&allocator);
END

TEST(extract_ruby_three_erb_same_line_with_semicolons)
  hb_arena_T allocator;
  hb_arena_init(&allocator, MB(1));
  char* source = "<% a = 1 %> <% b = 2 %> <% c = 3 %>";
  char* result = herb_extract_ruby_with_semicolons(&allocator, source);

  ck_assert_str_eq(result, "   a = 1  ;    b = 2  ;    c = 3   ");

  free(result);
  hb_arena_free(&allocator);
END

TEST(extract_ruby_different_lines_no_semicolons)
  hb_arena_T allocator;
  hb_arena_init(&allocator, MB(1));

  char* source = "<% x = 1 %>\n<% y = 2 %>";
  char* result = herb_extract_ruby_with_semicolons(&allocator, source);

  char expected[] = "   x = 1   \n   y = 2   ";
  ck_assert_str_eq(result, expected);

  free(result);
END

TEST(extract_ruby_mixed_lines)
  hb_arena_T allocator;
  hb_arena_init(&allocator, MB(1));

  char* source = "<% a = 1 %> <% b = 2 %>\n<% c = 3 %>";
  char* result = herb_extract_ruby_with_semicolons(&allocator, source);

  char expected[] = "   a = 1  ;    b = 2   \n   c = 3   ";
  ck_assert_str_eq(result, expected);

  free(result);
  hb_arena_free(&allocator);
END

TEST(extract_ruby_output_tags_same_line)
  hb_arena_T allocator;
  hb_arena_init(&allocator, MB(1));

  char* source = "<%= x %> <%= y %>";
  char* result = herb_extract_ruby_with_semicolons(&allocator, source);

  ck_assert_str_eq(result, "    x  ;     y   ");

  free(result);
  hb_arena_free(&allocator);
END

TEST(extract_ruby_empty_erb_same_line)
  hb_arena_T allocator;
  hb_arena_init(&allocator, MB(1));

  char* source = "<%  %> <%  %>";
  char* result = herb_extract_ruby_with_semicolons(&allocator, source);

  ck_assert_str_eq(result, "     ;       ");

  free(result);
  hb_arena_free(&allocator);
END

TEST(extract_ruby_comments_skipped)
  hb_arena_T allocator;
  hb_arena_init(&allocator, MB(1));

  char* source = "<%# comment %> <% code %>";
  char* result = herb_extract_ruby_with_semicolons(&allocator, source);

  ck_assert_str_eq(result, "                  code   ");

  free(result);
  hb_arena_free(&allocator);
END

TEST(extract_ruby_issue_135_if_without_condition)
  hb_arena_T allocator;
  hb_arena_init(&allocator, MB(1));

  char* source = "<% if %>\n<% end %>";
  char* result = herb_extract_ruby_with_semicolons(&allocator, source);

  char expected[] = "   if   \n   end   ";
  ck_assert_str_eq(result, expected);

  free(result);
  hb_arena_free(&allocator);
END

TEST(extract_ruby_inline_comment_same_line)
  hb_arena_T allocator;
  hb_arena_init(&allocator, MB(1));

  char* source = "<% if true %><% # Comment here %><% end %>";
  char* result = herb_extract_ruby_with_semicolons(&allocator, source);

  ck_assert_str_eq(result, "   if true  ;                       end   ");

  free(result);
  hb_arena_free(&allocator);
END

TEST(extract_ruby_inline_comment_with_newline)
  hb_arena_T allocator;
  hb_arena_init(&allocator, MB(1));

  char* source = "<% if true %><% # Comment here %>\n<% end %>";
  char* result = herb_extract_ruby_with_semicolons(&allocator, source);

  char expected[] = "   if true  ;                    \n   end   ";
  ck_assert_str_eq(result, expected);

  free(result);
  hb_arena_free(&allocator);
END

TEST(extract_ruby_inline_comment_with_spaces)
  hb_arena_T allocator;
  hb_arena_init(&allocator, MB(1));

  char* source = "<%  # Comment %> <% code %>";
  char* result = herb_extract_ruby_with_semicolons(&allocator, source);

  ck_assert_str_eq(result, "                    code   ");

  free(result);
  hb_arena_free(&allocator);
END

TEST(extract_ruby_inline_comment_multiline)
  hb_arena_T allocator;
  hb_arena_init(&allocator, MB(1));

  char* source = "<% # Comment\nmore %> <% code %>";
  char* result = herb_extract_ruby_with_semicolons(&allocator, source);

  char expected[] = "   # Comment\nmore  ;    code   ";
  ck_assert_str_eq(result, expected);

  free(result);
  hb_arena_free(&allocator);
END

TEST(extract_ruby_inline_comment_between_code)
  hb_arena_T allocator;
  hb_arena_init(&allocator, MB(1));

  char* source = "<% if true %><% # Comment here %><%= hello %><% end %>";
  char* result = herb_extract_ruby_with_semicolons(&allocator, source);

  ck_assert_str_eq(result, "   if true  ;                        hello  ;   end   ");

  free(result);
  hb_arena_free(&allocator);
END

TEST(extract_ruby_inline_comment_complex)
  hb_arena_T allocator;
  hb_arena_init(&allocator, MB(1));

  char* source = "<% # Comment here %><% if true %><% # Comment here %><%= hello %><% end %>";
  char* result = herb_extract_ruby_with_semicolons(&allocator, source);

  ck_assert_str_eq(result, "                       if true  ;                        hello  ;   end   ");

  free(result);
  hb_arena_free(&allocator);
END

TCase *extract_tests(void) {
  TCase *extract = tcase_create("Extract");

  tcase_add_test(extract, extract_ruby_single_erb_no_semicolon);
  tcase_add_test(extract, extract_ruby_multiple_erb_same_line_with_semicolon);
  tcase_add_test(extract, extract_ruby_three_erb_same_line_with_semicolons);
  tcase_add_test(extract, extract_ruby_different_lines_no_semicolons);
  tcase_add_test(extract, extract_ruby_mixed_lines);
  tcase_add_test(extract, extract_ruby_output_tags_same_line);
  tcase_add_test(extract, extract_ruby_empty_erb_same_line);
  tcase_add_test(extract, extract_ruby_comments_skipped);
  tcase_add_test(extract, extract_ruby_issue_135_if_without_condition);
  tcase_add_test(extract, extract_ruby_inline_comment_same_line);
  tcase_add_test(extract, extract_ruby_inline_comment_with_newline);
  tcase_add_test(extract, extract_ruby_inline_comment_with_spaces);
  tcase_add_test(extract, extract_ruby_inline_comment_multiline);
  tcase_add_test(extract, extract_ruby_inline_comment_between_code);
  tcase_add_test(extract, extract_ruby_inline_comment_complex);

  return extract;
}
