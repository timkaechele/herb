#include "include/test.h"
#include "../../src/include/herb.h"

TEST(herb_lex_to_buffer_empty_file)
  char* html = "";
  buffer_T output = buffer_new();

  herb_lex_to_buffer(html, &output);

  ck_assert_str_eq(output.value, "#<Token type=TOKEN_EOF value='' range=[0, 0] start=1:0 end=1:0>\n");

  buffer_free(&output);
END

TEST(herb_lex_to_buffer_basic_tag)
  char* html = "<html></html>";
  buffer_T output = buffer_new();

  herb_lex_to_buffer(html, &output);

  ck_assert_str_eq(
    output.value,
    "#<Token type=TOKEN_HTML_TAG_START value='<' range=[0, 1] start=1:0 end=1:1>\n"
    "#<Token type=TOKEN_IDENTIFIER value='html' range=[1, 5] start=1:1 end=1:5>\n"
    "#<Token type=TOKEN_HTML_TAG_END value='>' range=[5, 6] start=1:5 end=1:6>\n"
    "#<Token type=TOKEN_HTML_TAG_START_CLOSE value='</' range=[6, 8] start=1:6 end=1:8>\n"
    "#<Token type=TOKEN_IDENTIFIER value='html' range=[8, 12] start=1:8 end=1:12>\n"
    "#<Token type=TOKEN_HTML_TAG_END value='>' range=[12, 13] start=1:12 end=1:13>\n"
    "#<Token type=TOKEN_EOF value='' range=[13, 13] start=1:13 end=1:13>\n"
  );

  buffer_free(&output);
END

TCase *lex_tests(void) {
  TCase *tags = tcase_create("Lex");

  tcase_add_test(tags, herb_lex_to_buffer_empty_file);
  tcase_add_test(tags, herb_lex_to_buffer_basic_tag);

  return tags;
}
