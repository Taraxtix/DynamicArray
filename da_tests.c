/**
 * @file da_tests.c (Implementation of the tests)
 * @author : Taraxtix (Brauer Antonin)
 */

#define DS_IMPLEMENTATION
#include "da_tests.h"
#include "da.h"

bool test_create() {
    bool ret_value = true;

    const char *str = "abcdefghijklmnop";
    // TODO :FIGURE OUT WHY STRLEN SEGFAULT
    DynamicString *ds1 = DS(str);
    DynamicString *ds2 = DS_create_from_string_parts(str, 8);
    DynamicString *ds3 = DS("");
    DynamicString *ds4 = DS(NULL);
    if (ds1->size != 16 || ds2->size != 8 || ds3->size != 0 || ds4->size != 0) DEFER_RETURN(false);
    for (int i = 0; i < ds1->size; i++)
    {
        if (ds2->data[i] != str[i]) DEFER_RETURN(false);
        if (i < ds2->size && ds2->data[i] != str[i]) DEFER_RETURN(false);
    }

defer:
    DS_destroy(ds1);
    DS_destroy(ds2);
    DS_destroy(ds3);
    DS_destroy(ds4);
    return ret_value;
}

bool test_destroy() {
    DynamicString *ds1 = DS("1234567890");
    DynamicString *ds2 = DS("");
    DynamicString *ds3 = DS(NULL);

    DS_destroy(ds1);
    DS_destroy(ds2);
    DS_destroy(ds3);
    return true;
}

bool test_clear() {
    bool ret_value = true;

    DynamicString *ds1 = DS("1234567890");
    DS_clear(ds1);

    if (ds1->size != 0) DEFER_RETURN(false);

defer:
    DS_destroy(ds1);
    return ret_value;
}

bool test_get_char_at() {
    bool ret_value = true;

    DynamicString *ds1 = DS("0123456789");

    for (size_t i = 0; i < ds1->size; i++)
    {
        if (DS_get_char_at(ds1, i) != (char)INT_TO_CHAR(i)) DEFER_RETURN(false);
    }

defer:
    DS_destroy(ds1);
    return ret_value;
}

bool test_set_char_at() {
    bool ret_value = true;

    DynamicString *ds1 = DS("xxxxxxxxxx");
    for (int i = 0; i < ds1->size; i++)
    {
        DS_set_char_at(ds1, i, (char)INT_TO_CHAR(i));
        if (ds1->data[i] != (char)INT_TO_CHAR(i)) DEFER_RETURN(false);
    }

defer:
    DS_destroy(ds1);
    return ret_value;
}

bool test_equal() {
    bool ret_value = true;

    DynamicString *ds1 = DS("1234567890");
    DynamicString *ds2 = DS("1234567890x");
    if (DS_equal(ds1, ds2)) DEFER_RETURN(false);
    ds2->size--;
    DEFER_RETURN(DS_equal(ds1, ds2));

defer:
    DS_destroy(ds1);
    DS_destroy(ds2);
    return ret_value;
}

bool test_is_first() {
    bool ret_value = true;

    DynamicString *ds1 = DS("0");
    DEFER_RETURN(DS_is_first(ds1, '0'));

defer:
    DS_destroy(ds1);
    return ret_value;
}

bool test_append_char() {
    bool ret_value = true;

    DynamicString *ds1 = DS("");
    DS_append_char(ds1, '0');
    DEFER_RETURN(ds1->size == 1 && DS_is_first(ds1, '0'));

defer:
    DS_destroy(ds1);
    return ret_value;
}

bool test_append_string() {
    bool ret_value = true;

    DynamicString *ds1 = DS("");
    DS_append_str(ds1, "0123456789", 10);
    DEFER_RETURN(DS_equal(ds1, DS("0123456789")));

defer:
    DS_destroy(ds1);
    return ret_value;
}

bool test_remove_char_at() {
    bool ret_value = true;

    DynamicString *ds1 = DS("0123x456789");
    DS_remove_char_at(ds1, 4);
    DEFER_RETURN(DS_equal(ds1, DS("0123456789")));

defer:
    DS_destroy(ds1);
    return ret_value;
}

bool test_remove_string_at() {
    bool ret_value = true;

    DynamicString *ds1 = DS("0123Hello World!456789");
    DS_remove_str_at(ds1, 4, 15);
    DEFER_RETURN(DS_equal(ds1, DS("0123456789")));

defer:
    DS_destroy(ds1);
    return ret_value;
}

bool test_substring() {
    bool ret_value = true;

    DynamicString *ds1 = DS("0123Hello World!456789");
    DynamicString *ds2 = DS_substring(ds1, 4, 15);
    DEFER_RETURN(DS_equal(ds2, DS("Hello World!")) && DS_equal(ds1, DS("0123Hello World !456789")));

defer:
    DS_destroy(ds1);
    DS_destroy(ds2);
    return ret_value;
}

bool test_chop_first() {
    bool ret_value = true;

    DynamicString *ds1 = DS("0123Hello World!456789");
    DynamicString *ds2 = DS_chop_first(ds1);
    DEFER_RETURN(DS_equal(ds1, DS("123Hello World!456789")) && DS_equal(ds2, DS("0")));

defer:
    DS_destroy(ds1);
    DS_destroy(ds2);
    return ret_value;
}

bool test_chop_last() {
    bool ret_value = true;

    DynamicString *ds1 = DS("0123Hello World!456789");
    DynamicString *ds2 = DS_chop_last(ds1);
    DEFER_RETURN(DS_equal(ds1, DS("0123Hello World!45678")) && DS_equal(ds2, DS("9")));

defer:
    DS_destroy(ds1);
    DS_destroy(ds2);
    return ret_value;
}

bool test_chop_right() {
    bool ret_value = true;

    DynamicString *ds1 = DS("0123Hello World!456789");
    DynamicString *ds2 = DS_chop_right(ds1, 4);
    DEFER_RETURN(DS_equal(ds1, DS("Hello World!456789")) && DS_equal(ds2, DS("0123")));

defer:
    DS_destroy(ds1);
    DS_destroy(ds2);
    return ret_value;
}

bool test_chop_left() {
    bool ret_value = true;

    DynamicString *ds1 = DS("0123Hello World!456789");
    DynamicString *ds2 = DS_chop_left(ds1, 4);
    DEFER_RETURN(ds1->size == 11 && DS_equal(ds2, DS("Hello World!456789")) &&
                 DS_equal(ds1, DS("0123")));

defer:
    DS_destroy(ds1);
    DS_destroy(ds2);
    return ret_value;
}

bool test_chop_by_delim() {
    bool ret_value = true;

    DynamicString *ds1 = DS("0123Hello World!456789");
    DynamicString *ds2 = DS_chop_by_delim(ds1, '3');
    DEFER_RETURN(ds1->size == 11 && DS_equal(ds1, DS("Hello World!456789")) &&
                 DS_equal(ds2, DS("0123")));

defer:
    DS_destroy(ds1);
    DS_destroy(ds2);
    return ret_value;
}