/**
 * @file : da.h (Main implementation of DynamicArray library)
 * @author : Taraxtix (Antonin Brauer)
 */

#ifndef DA_H
#define DA_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifndef DA_DEF
    #define DA_DEF
#endif // DA_DEF

#define ASSERT(cond, msg)                                             \
    do {                                                              \
        if (!(cond)) {                                                \
            fprintf(stderr, "[ERROR] Assertion failed: %s\n", (msg)); \
            exit(1);                                                  \
        }                                                             \
    } while (0)

#define DA_GET(da, type, index) (type) * (DA_get((da), (index)))

typedef struct {
    size_t size;
    size_t capacity;
    void **data;
} DynamicArray;

/******************************************************************************/
/*                           FUNCTIONS DECLARATIONS                           */
/******************************************************************************/

DA_DEF DynamicArray *DA_create_empty();
DA_DEF DynamicArray *DA_create_from_array(const void **array, size_t size);
DA_DEF void DA_destroy(DynamicArray *da);
DA_DEF DynamicArray *DA_copy(const DynamicArray *da);
DA_DEF bool DA_equal(const DynamicArray *da1, const DynamicArray *da2);
DA_DEF void DA_clear(DynamicArray *da);
DA_DEF void DA_push_back(DynamicArray *da, void *element);
DA_DEF void *DA_pop_back(DynamicArray *da);
DA_DEF void DA_push_front(DynamicArray *da, void *element);
DA_DEF void *DA_pop_front(DynamicArray *da);
DA_DEF void *DA_get(const DynamicArray *da, size_t index);
DA_DEF void DA_set(DynamicArray *da, size_t index, void *element);
DA_DEF void DA_insert_before(DynamicArray *da, size_t index, void *element);
DA_DEF void DA_insert_after(DynamicArray *da, size_t index, void *element);
DA_DEF void DA_remove_at(DynamicArray *da, size_t index);
DA_DEF void DA_remove_after(DynamicArray *da, size_t index);
DA_DEF void DA_remove_before(DynamicArray *da, size_t index);

#endif // DA_DEF
#ifdef DA_IMPLEMENTATION

/******************************************************************************/
/*                          FUNCTIONS IMPLEMENTATION                          */
/******************************************************************************/

DA_DEF DynamicArray *DA_create_empty() {
    DynamicArray *da = (DynamicArray *)malloc(sizeof(DynamicArray));
    ASSERT(da, "Cannot allocate memory for dynamic array.");
    da->size = 0;
    da->capacity = 128;
    da->data = malloc(sizeof(void *) * da->capacity);
    ASSERT(da->data, "Cannot allocate memory for dynamic array.");
    return da;
}

DA_DEF DynamicArray *DA_create_from_array(const void **array, size_t size) {
    DynamicArray *da = DA_create_empty();
    da->size = size;
    while (da->capacity <= size) {
        da->capacity *= 2;
        da->data = realloc(da->data, sizeof(void *) * da->capacity);
        ASSERT(da->data, "Cannot allocate memory for dynamic array.");
    }
    memcpy(da->data, array, sizeof(void *) * size);
    return da;
}

DA_DEF void DA_destroy(DynamicArray *da) {
    if (da) free(da->data);
    free(da);
}

DA_DEF DynamicArray *DA_copy(const DynamicArray *da) {
    return DA_create_from_array((const void **)da->data, da->size);
}

DA_DEF bool DA_equal(const DynamicArray *da1, const DynamicArray *da2) {
    if (da1->size != da2->size) return false;
    for (size_t i = 0; i < da1->size; i++) {
        if (da1->data[i] != da2->data[i]) return false;
    }
    return true;
}

DA_DEF void DA_clear(DynamicArray *da) { da->size = 0; }

DA_DEF void DA_push_back(DynamicArray *da, void *element) {
    if (da->size == da->capacity) {
        da->capacity *= 2;
        da->data = realloc(da->data, sizeof(void *) * da->capacity);
        ASSERT(da->data, "Cannot allocate memory for dynamic array.");
    }
    da->data[da->size] = element;
    da->size += 1;
}

DA_DEF void *DA_pop_back(DynamicArray *da) {
    void *element = da->data[da->size - 1];
    da->size -= 1;
    return element;
}

DA_DEF void DA_push_front(DynamicArray *da, void *element) {
    if (da->size == da->capacity) {
        da->capacity *= 2;
        da->data = realloc(da->data, sizeof(void *) * da->capacity);
        ASSERT(da->data, "Cannot allocate memory for dynamic array.");
    }
    memmove(da->data + 1, da->data, da->size * sizeof(void *));
    da->data[0] = element;
    da->size += 1;
}

DA_DEF void *DA_pop_front(DynamicArray *da) {
    void *element = da->data[0];
    da->size -= 1;
    memmove(da->data, da->data + 1, da->size * sizeof(void *));
    return element;
}

DA_DEF void *DA_get(const DynamicArray *da, size_t index) { return da->data[index]; }

DA_DEF void DA_set(DynamicArray *da, size_t index, void *element) { da->data[index] = element; }

// Size = 10
// Index = 4
// 0123456789

DA_DEF void DA_insert_before(DynamicArray *da, size_t index, void *element) {
    memmove(da->data + index + 1, da->data + index, (da->size - index) * sizeof(void *));
    da->data[index] = element;
}

DA_DEF void DA_insert_after(DynamicArray *da, size_t index, void *element) {
    DA_insert_before(da, index + 1, element);
}

DA_DEF void DA_remove_at(DynamicArray *da, size_t index) {
    da->size -= 1;
    memmove(da->data + index, da->data + index + 1, (da->size - index) * sizeof(void *));
}

DA_DEF void DA_remove_after(DynamicArray *da, size_t index) { da->size -= (index + 1); }

DA_DEF void DA_remove_before(DynamicArray *da, size_t index) {
    memmove(da->data, da->data + index, (da->size - index) * sizeof(void *));
    da->size -= index;
}

#endif // DA_IMPLEMENTATION