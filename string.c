#include <assert.h>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <err.h>

#include "string.h"

#define CASE_GAP                    (32U)

// Operation
#define a_is_b(a, b)                ((a) == (b))
#define is_null_ptr(a)              ((a) == NULL)
#define is_a_null(a)                (is_null_ptr(a) << 1U)
#define is_b_null(b)                (is_null_ptr(b) << 2U)
#define set_flag(offset)            ((1U) << offset)  

typedef enum variants {
    CAP_VAR,
    CASE_FOLD_VAR,
}variants_t;

#define NO_VARIANTS                 (0U)
#define set_variant(var)            (set_flag(var))
#define is_variant_set(x, var)      (x & set_flag(var))

typedef struct slice {
    struct slice* next;
    uint32_t length;
    variants_t variant;
    str_t str;
}slice_t;

struct string {
    uint32_t length;
    uint32_t variants;
    char* text;
    slice_t* slices;
};

// Basic text methods
static inline uint32_t size(const char *text) {
    uint32_t size = 0U;

    while (text[size++] != '\0');

    return size;
}

static inline void copy(char* dest, const char *text, uint32_t len) {
    for (uint32_t i = 0; i < len; i++) {
        dest[i] = text[i];
    }
    
    dest[len - 1U] = '\0';
}

static inline str_result compare(const char *a, const char *b, uint32_t len) {
    for (uint32_t i = 0; i < len; i++) {
        if (a[i] != b[i]) {
            return No_equal;
        }
    }

    return Equal;
}

// Slice method
void print_slice(slice_t *slice) {
    printf("slice: %p\n", slice);
    printf("-> text: %s\n", slice->str);
    printf("-> length: %u\n", slice->length);
    printf("-> next ptr: %p\n", slice->next);
}

void print_linkedlist(slice_t *head) {
    uint32_t n = 0;
    slice_t *slice = head;

    printf("Printing linkedlist\n");

    while(slice != NULL) {
        print_slice(slice);
        slice = slice->next;
        n++;
    }

    printf("linkedlist has %u elements\n", n);
}

slice_t* new_slice(str_t str) {
    if (is_null_ptr(str)) {
        return NULL;
    }

    slice_t *slice = malloc(sizeof(slice_t));

    if (is_null_ptr(slice)) {
        return NULL;
    }

    slice->length = size(str);

    char* text = malloc(slice->length);

    if (is_null_ptr(text)) {
        return NULL;
    }

    copy(text, str, slice->length);
    slice->str = text;

    slice->next = NULL;

    return slice;
}

void remove_slices(slice_t **head) {
    slice_t *curr = *head;
    slice_t *next = curr->next;

    while(curr != NULL) {
        printf("Removing ");
        print_slice(curr);
        next = curr->next;
        free(curr);
        curr = next;
    }

    *head = NULL;
}

slice_t* append_slice(slice_t **head, str_t str) {

    if (*head == NULL) {
        *head = new_slice(str);
        return *head;
    }

    slice_t *slice = *head;
    while (slice->next != NULL) {
        slice = slice->next;
    }

    slice->next = new_slice(str);

    return slice->next;
}

slice_t* search_slice(slice_t **head, variants_t variant) {
    slice_t *slice = *head;

    while ((slice != NULL) && (slice->variant != variant)) {
        slice = slice->next;
    }

    return slice;
}

void print_string(string_t string) {
    printf("String: '%s' { \n", string->text);
    printf("length: %u\n", string->length);
    printf("Location:  %p {\n", string);
    printf(" length: %p\n", &string->length);
    printf(" text: %p\n", &string->text);
    printf(" slices: %p\n", &string->slices);
    printf(" }\n");
    print_linkedlist(string->slices);
    printf("}\n");
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
    printf("destroy\n");
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
        return NULL_PTR;
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

int main(int argc, char *argv[])
{
    string_t string = string_new("paco MEMO");

    assert(string != NULL);

    assert(string_len(string) == 9);

    assert(str_equal(string, "paco MEMO") == Equal);

    str_t txt = string_capitalize(string);
    assert(text_equal(txt, "Paco MEMO") == Equal);

    txt = string_capitalize(string);
    printf("%s\n", txt);

    txt = string_case_fold(string);
    assert(text_equal(txt, "paco memo") == Equal);

    txt = string_capitalize(string);
    printf("%s\n", txt);

    string_destroy(&string);
    assert(string == NULL);

    return 0;
}
