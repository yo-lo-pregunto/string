/**
 * @file doxygen_c.h
 * @author My Self
 * @date 9 Sep 2012
 * @brief File containing example of doxygen usage for quick reference.
 *
 * Here typically goes a more extensive explanation of what the header
 * defines. Doxygens tags are words preceeded by either a backslash @\
 * or by an at symbol @@.
 * @see http://www.stack.nl/~dimitri/doxygen/docblocks.html
 * @see http://www.stack.nl/~dimitri/doxygen/commands.html
 */

#ifndef _STRING_H_
#define _STRING_H_

// Standar libraries
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct string string;
typedef string* string_t;

typedef const char* str_t;

typedef enum str_result {
    Equal = 0,
    No_equal,
    A_is_null,
    B_is_null,

}str_result;

/*!
 * @brief Create a new String.
 *
 * @param text to be allocated on heap.
 *
 * @return a String object.
 */
string_t string_new(const char *text);

/*!
 * @brief Destroy a String object.
 *
 * @param *string pointer to a String object.
 *
 * @return void
 */
void string_destroy(string_t *string);

const char* string_text(string_t string);

/*!
 * @brief Get the string lenght.
 *
 * @params String object
 *
 * @return A positive value or NULL_PTR
 */
int32_t string_len(string_t string);

/*!
 * @brief Converts the first character to upper case.
 *
 * @param String object
 *
 * @return string slice.
 */
str_t string_capitalize(string_t string);

/*!
 * @brief Converts string into lower case.
 *
 * @param String object
 *
 * @return void
 */
str_t string_case_fold(string_t string);

str_t string_center(string_t string, uint32_t len, char c);

// String operation

/*!
 * @brief Compare two String obj.
 *
 * @param String object one.
 * @param String object two.
 *
 * @return str_result enum.
 */
str_result string_equal(string_t a, string_t b);

/*!
 * @brief Compare a String obj vesus text.
 *
 * @param String object one.
 * @param const char* text.
 *
 * @return str_result enum.
 */
str_result str_equal(string_t string, const char* text);

/*!
 * @brief Compare two text.
 *
 * @param const char* text one.
 * @param const char* text two.
 *
 * @return str_result enum.
 */
str_result text_equal(str_t a, str_t b);

#endif // !_STRING_H_
