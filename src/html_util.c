#include "include/html_util.h"
#include "include/util.h"
#include "include/util/hb_buffer.h"
#include "include/util/hb_string.h"

#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

// https://developer.mozilla.org/en-US/docs/Glossary/Void_element
bool is_void_element(hb_string_T tag_name) {
  if (hb_string_is_empty(tag_name)) { return false; }

  hb_string_T void_tags[14] = {
    hb_string_from_c_string("area"),  hb_string_from_c_string("base"),  hb_string_from_c_string("br"),
    hb_string_from_c_string("col"),   hb_string_from_c_string("embed"), hb_string_from_c_string("hr"),
    hb_string_from_c_string("img"),   hb_string_from_c_string("input"), hb_string_from_c_string("link"),
    hb_string_from_c_string("meta"),  hb_string_from_c_string("param"), hb_string_from_c_string("source"),
    hb_string_from_c_string("track"), hb_string_from_c_string("wbr"),
  };

  for (size_t i = 0; i < 14; i++) {
    if (hb_string_equals_case_insensitive(tag_name, void_tags[i])) { return true; }
  }

  return false;
}

/**
 * @brief Creates a closing HTML tag string like "</tag_name>"
 *
 * @param tag_name The name of the HTML tag to be enclosed in a closing tag
 * @return A newly allocated string containing the closing tag, or NULL if memory allocation fails
 * @note The caller is responsible for freeing the returned string
 *
 * Example:
 * @code
 * char* tag = html_closing_tag_string("div");
 * if (tag) {
 *   printf("%s\n", tag); // Prints: </div>
 *   free(tag);
 * }
 * @endcode
 */
char* html_closing_tag_string(const char* tag_name) {
  if (tag_name == NULL) { return herb_strdup("</>"); }

  hb_buffer_T buffer;
  hb_buffer_init(&buffer, strlen(tag_name) + 3);

  hb_buffer_append_char(&buffer, '<');
  hb_buffer_append_char(&buffer, '/');
  hb_buffer_append(&buffer, tag_name);
  hb_buffer_append_char(&buffer, '>');

  return buffer.value;
}

/**
 * @brief Creates a self-closing HTML tag string like "<tag_name />"
 *
 * @param tag_name The name of the HTML tag to be enclosed in a self-closing tag
 * @return A newly allocated string containing the self-closing tag, or NULL if memory allocation fails
 * @note The caller is responsible for freeing the returned string
 *
 * Example:
 * @code
 * char* tag = html_self_closing_tag_string("br");
 * if (tag) {
 *   printf("%s\n", tag); // Prints: <br />
 *   free(tag);
 * }
 * @endcode
 */
char* html_self_closing_tag_string(const char* tag_name) {
  if (tag_name == NULL) { return herb_strdup("< />"); }

  hb_buffer_T buffer;
  hb_buffer_init(&buffer, strlen(tag_name) + 4);

  hb_buffer_append_char(&buffer, '<');
  hb_buffer_append(&buffer, tag_name);
  hb_buffer_append_char(&buffer, ' ');
  hb_buffer_append_char(&buffer, '/');
  hb_buffer_append_char(&buffer, '>');

  return buffer.value;
}
