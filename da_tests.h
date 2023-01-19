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

bool test_create();
bool test_destroy();
bool test_clear();

#endif // DA_TESTS_H