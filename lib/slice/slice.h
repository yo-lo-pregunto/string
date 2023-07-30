/**
 * @file slice.h
 * @author yo-lo-pregunto
 * @date 23 July 2023
 * @brief Base class for Slice object.
 *
 */
#ifndef _SLICE_H_
#define _SLICE_H_

#include "base.h"

typedef struct slice {
    struct slice* next;
    uint32_t length;
    variants_t variant;
    str_t str;
}slice_t;

extern slice_t* new_slice(str_t str);
extern void remove_slices(slice_t **head);
extern slice_t* append_slice(slice_t **head, str_t str);
extern slice_t* search_slice(slice_t **head, variants_t variant);

#endif // !_SLICE_H_
