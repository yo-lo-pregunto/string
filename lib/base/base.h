/**
 * @file base.h
 * @author yo-lo-pregunto
 * @date 23 July 2023
 * @brief Basic bit operations and checks.
 *
 */

#ifndef _BASE_H_
#define _BASE_H_

#include <stdint.h>

typedef const char* str_t;

/* 
 * @brief Set single bit at pos to '1' by generating a mask
 * in the proper bit location and ORing (|) x with the mask. 
 */
#define SET_BIT(x, pos)             (x |= (1U << pos))

/* 
 * @brief Set single bit at pos to '0' by generating a mask
 * in the proper bit location and Anding x with the mask. 
 */
#define CLEAR_BIT(x, pos)           (x &= (~(1U<< pos)))

/*
 * @brief Set single bit at pos to '1' by generating a mask
 * in the proper bit location and ex-ORing x with the mask. 
 */
#define TOGGLE_BIT(x, pos)          (x ^= (1U<< pos))

/*
 * @brief Set single bit at pos to '1' by generating a mask
 * in the proper bit location and Anding x with the mask.
 * It evaluates 1 if a bit is set otherwise 0.
*/
#define CHECK_BIT(x, pos)           (x & (1UL << pos))

/*! @brief Check if two pointers are equal */
#define a_is_b(a, b)                ((void*)(a) == (void*)(b))

/*! @brief Check if is a NULL pointer */
#define is_null_ptr(a)              ((a) == NULL)

#define TRUE                        (0U)

#define FALSE                       (1U)

#define EQUAL                       TRUE

#define NOT_EQUAL                   FALSE

typedef enum variants {
    CAP_VAR,
    CASE_FOLD_VAR,
}variants_t;

static inline uint32_t size(str_t text) {
    uint32_t size = 0U;

    while (text[size++] != '\0');

    return size;
}

static inline void copy(char *dest, str_t text, uint32_t len) {
    for (uint32_t i = 0; i < len; i++) {
        dest[i] = text[i];
    }
    
    dest[len - 1U] = '\0';
}

static inline int compare(str_t a, str_t b, uint32_t len) {
    for (uint32_t i = 0; i < len; i++) {
        if (a[i] != b[i]) {
            return NOT_EQUAL;
        }
    }

    return EQUAL;
}

#endif // !_BASE_H_
