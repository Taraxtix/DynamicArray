/**
 * @file : da_tests.h (Test declaration)
 * @author : Taraxtix (Brauer Antonin)
 */

#ifndef DA_TESTS_H
#define DA_TESTS_H

#include <stdbool.h>

#define DEFER_RETURN(ret)  \
    do                     \
    {                      \
        ret_value = (ret); \
        goto defer;        \
    } while (0)

#define INT_TO_CHAR(i) (i + 'a')

bool test_create();
bool test_destroy();
bool test_clear();
bool test_get_char_at();
bool test_set_char_at();
bool test_equal();
bool test_is_first();
bool test_append_char();
bool test_append_string();
bool test_remove_char_at();
bool test_remove_string_at();
bool test_substring();
bool test_chop_first();
bool test_chop_last();
bool test_chop_right();
bool test_chop_left();
bool test_chop_by_delim();

#endif // DA_TESTS_H