/**
 * @file slice.c
 * @author yo-lo-pregunto
 * @date 23 July 2023
 * @brief Base class for Slice object.
 */

#include <stdio.h>
#include <stdlib.h>

#include "slice.h"

// Slice method
static void print_slice(slice_t *slice) {
//    printf("slice: %p\n", slice);
//    printf("-> text: %s\n", slice->str);
//    printf("-> length: %u\n", slice->length);
//    printf("-> next ptr: %p\n", slice->next);
}

static void print_linkedlist(slice_t *head) {
    uint32_t n = 0;
    slice_t *slice = head;

//    printf("Printing linkedlist\n");

    while(slice != NULL) {
        print_slice(slice);
        slice = slice->next;
        n++;
    }

//    printf("linkedlist has %u elements\n", n);
}

slice_t* new_slice(str_t str) {
    if (str == NULL) {
        return NULL;
    }

    slice_t *slice = malloc(sizeof(slice_t));

    if (slice == NULL) {
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
