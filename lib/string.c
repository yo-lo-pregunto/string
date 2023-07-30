/**
 * @file string.c
 * @author yo-lo-pregunto
 * @date 23 July 2023
 * @brief Base class for String object.
 *
 */

#include <stdio.h>

#include "string.h"
#include "slice.h"

/*! @brief Distance between lower and uppercase in a ASCII table */
#define CASE_GAP                    (32U)

/*! @brief Shift One to the left 'offset' positions */
#define set_flag(offset)            ((1U) << offset)  

/*! @brief No Variant has been created */
#define NO_VARIANTS                 (0U)

/*! @brief Set a variant to a variable */
#define set_variant(var)            (set_flag(var))

/*! @brief Check if a variants is set */
#define is_variant_set(x, var)      (x & set_flag(var))


struct string {
    uint32_t length;
    uint32_t variants;
    char* text;
    slice_t* slices;
};

void print_string(string_t string) {
//    printf("String: '%s' { \n", string->text);
//    printf("length: %u\n", string->length);
//    printf("Location:  %p {\n", string);
//    printf(" length: %p\n", &string->length);
//    printf(" text: %p\n", &string->text);
//    printf(" slices: %p\n", &string->slices);
//    printf(" }\n");
//    print_linkedlist(string->slices);
//    printf("}\n");
}

string_t string_new(const char *text) {

    if (is_null_ptr(text)) {
        return NULL;
    }

    string_t string = (string_t)malloc(sizeof(string_t));

    if (is_null_ptr(string)) {
        return NULL;
    }

    string->variants = NO_VARIANTS;
    string->length = size(text);
    string->text = (char*)malloc(string->length);

    if (is_null_ptr(string->text)) {
        return NULL;
    }

    copy(string->text, text, string->length);

    string->slices = NULL;
    print_string(string);

    return string;
}

void string_destroy(string_t *string) {
//    printf("destroy\n");
    if (is_null_ptr(string)) {
        return;
    }
    
    if (((string_t)*string)->text) {
        free(((string_t)*string)->text);
        ((string_t)*string)->text = NULL;
    }

    ((string_t)*string)->length = 0U;
    remove_slices(&((string_t)*string)->slices);

    free(((string_t)*string));

    *string = NULL;
}

str_t string_text(string_t string) {
    if ((is_null_ptr(string)) || (is_null_ptr(string->text)))  {
        return NULL;
    }

    return (const char*) string->text;
}

int32_t string_len(string_t string) {
    if (is_null_ptr(string)) {
        return 1;
    }

    return string->length - 1U;
}

str_t string_capitalize(string_t string) {
    if ((is_null_ptr(string)) || (is_null_ptr(string->text)))  {
        return NULL;
    }

    slice_t *slice;
    if (is_variant_set(string->variants, CAP_VAR)) {
        slice = search_slice(&string->slices, CAP_VAR);
        return slice->str;
    }
    
    slice = append_slice(&string->slices, string->text);
    if (is_null_ptr(slice)) {
        return NULL;
    }

    slice->variant = CAP_VAR;
    string->variants += set_variant(CAP_VAR);

    char *text = (char*)slice->str;

    if ((text[0] >= 'a') && (text[0] <= 'z')) {
        text[0] -= CASE_GAP; 
    }

    return slice->str;
}

str_t string_case_fold(string_t string) {
    if ((is_null_ptr(string)) || (is_null_ptr(string->text)))  {
        return NULL;
    }

    slice_t *slice;
    if (is_variant_set(string->variants, CASE_FOLD_VAR)) {
        slice = search_slice(&string->slices, CASE_FOLD_VAR);
        return slice->str;
    }
    
    slice = append_slice(&string->slices, string->text);
    if (is_null_ptr(slice)) {
        return NULL;
    }

    slice->variant = CASE_FOLD_VAR;
    string->variants += set_variant(CASE_FOLD_VAR);

    char *text = (char*)slice->str;

    for (uint32_t i = 0; i < slice->length; i++) {
        if ((text[i]) >= 'A' && (text[i] <= 'Z')) {
            text[i] += CASE_GAP;
        }
    }

    return slice->str;
}

str_result string_equal(string_t a, string_t b) {

    if (a_is_b(a, b)) {
        return Equal;
    }


    if (is_null_ptr(a)) {
        return A_is_null;
    }

    if (is_null_ptr(b)) {
        return B_is_null;
    }

    if (a->length != b->length) {
        return  No_equal;
    }

    if (is_null_ptr(a->text) || is_null_ptr(b->text)) {
        return No_equal;
    }

    return compare(a->text, (const char*)b->text, a->length);
}

str_result str_equal(string_t string, str_t text) {
    if (is_null_ptr(string) || is_null_ptr(text) || is_null_ptr(string->text)) {
        return No_equal;
    }

    return compare(string->text, text, string->length);
}

str_result text_equal(str_t a, str_t b) {
    if (a_is_b(a, b)) {
        return Equal;
    }


    if (is_null_ptr(a)) {
        return A_is_null;
    }

    if (is_null_ptr(b)) {
        return B_is_null;
    }

    return compare(a, b, size(a));
}
