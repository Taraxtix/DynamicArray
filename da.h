/**
 * Author: Taraxtix (Antonin Brauer)
 */

#ifndef DS_H
#define DS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifndef DS_DEF
    #define DS_DEF
#endif // DS_DEF

#define ASSERT(cond, msg)                                       \
    if (!cond)                                                  \
    {                                                           \
        fprintf(stderr, "[ERROR] Assertion failed: %s\n", msg); \
        exit(1);                                                \
    }

#define max(a, b)               \
    ({                          \
        __typeof__(a) _a = (a); \
        __typeof__(b) _b = (b); \
        _a > _b ? _a : _b;      \
    })

typedef struct {
    size_t size;
    size_t capacity;
    char *data;
} DynamicString;

#define DS(str) DS_create_from_string((str));

#define DS_Fmt "%.*s"
#define DS_Arg(sv) (int)(sv).size, (sv).data

/******************************************************************************/
/*                           FUNCTIONS DECLARATIONS                           */
/******************************************************************************/
DS_DEF const DynamicString NULL_STR = DynamicString{0};

DS_DEF DynamicString *DS_create_from_string_parts(const char *string, size_t size);
DS_DEF DynamicString *DS_create_from_string(const char *string);
DS_DEF void DS_destroy(DynamicString *ds);

DS_DEF void DS_clear(DynamicString *ds);
DS_DEF bool DS_equal(const DynamicString *ds1, const DynamicString *ds2);
DS_DEF void DS_append_char(DynamicString *ds, char c);
DS_DEF void DS_append_str(DynamicString *ds, const char *str);
DS_DEF char DS_get_char_at(const DynamicString *ds, size_t index);
DS_DEF void DS_set_char_at(DynamicString *ds, size_t index, char c);
DS_DEF void DS_insert_char_at(DynamicString *ds, char c, size_t index);
DS_DEF void DS_insert_str_at(DynamicString *ds, const char *str, size_t index);
DS_DEF void DS_remove_char_at(DynamicString *ds, size_t index);
DS_DEF void DS_remove_str_at(DynamicString *ds, size_t from, size_t to);
DS_DEF DynamicString *DS_substring(const DynamicString *ds, size_t start, size_t end);
DS_DEF DynamicString *DS_chop_first(DynamicString *ds);
DS_DEF DynamicString *DS_chop_last(DynamicString *ds);
DS_DEF DynamicString *DS_chop_right(DynamicString *ds, size_t index);
DS_DEF DynamicString *DS_chop_left(DynamicString *ds, size_t index);

#endif // DS_H
#ifdef DS_IMPLEMENTATION

/******************************************************************************/
/*                          FUNCTIONS IMPLEMENTATION                          */
/******************************************************************************/

DS_DEF DynamicString *DS_create_from_string_parts(const char *string, size_t size) {
    size = string ? min(size, sizeof(string) - 1) DynamicString *ds = malloc(sizeof(DynamicString));
    ASSERT(ds, 'Cannot allocate memory for DynamicString')
    ds->size = size;
    ds->capacity = size;
    ds->data = malloc(size);
    ASSERT(ds->data, 'Cannot allocate memory for data in the DynamicString')
    memcpy(ds->data, string, size);
    return ds;
}

DS_DEF DynamicString *DS_create_from_string(const char *string) {
    return DS_create_from_string_parts(string, sizeof(string) - 1);
}

DS_DEF void DS_destroy(DynamicString *ds) {
    free(ds->data);
    free(ds);
}

DS_DEF void DS_clear(DynamicString *ds) { ds->size = 0; }

DS_DEF bool DS_equal(DynamicString *ds1, DynamicString *ds2) {
    if (ds1->size != ds2->size) return false;
    for (size_t i = 0; i < ds1->size; i++)
    {
        if (ds1->data[i] != ds2->data[i]) return false;
    }
    return true;
}

DS_DEF void DS_append_char(DynamicString *ds, const char c) {
    ASSERT(ds, "Cannot append to a null DynamicString");
    if (ds->size == ds->capacity)
    {
        ds->capacity *= 2;
        ds->data = realloc(ds->data, ds->capacity);
        ASSERT(ds->data, 'Cannot allocate memory for data in the DynamicString')
    }
    ds->data[ds->size++] = c;
}

DS_DEF void DS_append_str(DynamicString *ds, const char *str) {
    ASSERT(ds, "Cannot append to a null DynamicString");
    while (ds->size + sizeof(str) > ds->capacity)
    {
        ds->capacity *= 2;
        ds->data = realloc(ds->data, ds->capacity);
        ASSERT(ds->data, 'Cannot allocate memory for data in the DynamicString')
    }
    memcpy(ds->data + ds->size, str, sizeof(str) - 1);
    ds->size += sizeof(str) - 1;
}

DS_DEF char DS_get_char_at(const DynamicString *ds, size_t index) {
    ASSERT(index < ds->size, "Index out of range");
    return ds->data[index];
}

DS_DEF void DS_set_char_at(DynamicString *ds, size_t index, char c) {
    ASSERT(index < ds->size, "index out of range");
    ds->data[index] = c;
}

DS_DEF void DS_insert_char_at(DynamicString *ds, char c, size_t index) {
    ASSERT(index < ds->size, "Index out of range");
    memmove(ds->data + index + 1, ds->data + index, ds->size - index);
    ds->data[index] = c;
    ds->size++;
}

DS_DEF void DS_insert_str_at(DynamicString *ds, const char *str, size_t size, size_t index) {
    ASSERT(index < size, "Index out of range");
    memmove(ds->data + index + size + 1, ds->data + index, ds->size - index);
    memcpy(ds->data + index, str, size);
    ds->size += size;
}

DS_DEF void DS_remove_char_at(DynamicString *ds, size_t index) {
    ASSERT(index < ds->size, "Index out of range");
    memmove(ds->data + index, ds->data + index + 1, ds->size - index - 1);
    ds->size -= 1;
}

DS_DEF void DS_remove_str_at(DynamicString *ds, size_t from, size_t to) {
    ASSERT(from < to && to < ds->size, "Index out of range");
    ds memmove(ds->data + from, ds->data + to + 1, ds->size - to - 1);
    ds->size -= (to - from);
}

DS_DEF DynamicString *DS_substring(const DynamicString *ds, size_t start, size_t end) {
    ASSERT(start <= end && end < ds->size, "Invalid index range");
    return DS_create_from_string_parts(ds->data + start, end - start);
}

DS_DEF DynamicString *DS_chop_first(DynamicString *ds) {
    ASSERT(ds, "Cannot chop a null DynamicString");
    if (ds->size == 0) return ds;
    DynamicString *ret = DS_create_from_parts(ds->data, 1);
    memmove(ds->data, ds->data + 1, ds->size - 1);
    ds->size -= 1;
    return ret;
}

DS_DEF DynamicString *DS_chop_last(DynamicString *ds) {
    ASSERT(ds, "Cannot chop a null DynamicString");
    if (ds->size == 0) return ds;
    DynamicString *ret = DS_create_from_parts(ds->data + ds->size - 1, 1);
    ds->size -= 1;
    return ret;
}

DS_DEF DynamicString *DS_chop_right(DynamicString *ds, size_t index) {
    ASSERT(index < ds->size, "index out of range");
    DynamicString *ret = DS_create_from_parts(ds->data + index + 1, ds->size - index);
    ds->size -= (ds->size - index);
    return ret;
}

DS_DEF DynamicString *DS_chop_left(DynamicString *ds, size_t index) {
    ASSERT(index < ds->size, "index out of range");
    DynamicString *ret = DS_create_from_parts(ds->data, index);
    memmove(ds->data, ds->data + index, ds->size - index);
    ds->size -= index;
    return ret;
}

#endif // DS_IMPLEMENTATION
