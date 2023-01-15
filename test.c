#include "da_tests.h"


#define USAGE(filename)                                       \
    do                                                        \
    {                                                         \
        fprintf(stderr, "Usage: %s <test name>", (filename)); \
        exit(1);                                              \
    } while (0)

typedef struct {
    char *name;
    int (*func)(void);
} Test;

Test tests[] = {

    {"test_create", test_create},
    {"test_destroy", test_destroy},
    {"test_clear", test_clear},
    {"test_get_char_at", test_get_char_at},
    {"test_set_char_at", test_set_char_at},
    {"test_equal", test_equal},
    {"test_is_first", test_is_first},
    {"test_append_char", test_append_char},
    {"test_append_string", test_append_string},
    {"test_remove_char_at", test_remove_char_at},
    {"test_remove_string_at", test_remove_string_at},
    {"test_substring", test_substring},
    {"test_chop_first", test_chop_first},
    {"test_chop_last", test_chop_last},
    {"test_chop_right", test_chop_right},
    {"test_chop_left", test_chop_left},
    {"test_chop_by_delim", test_chop_by_delim},
    // NULL_test
    {0, NULL},
};

int main(int argc, char **argv) {
    if (argc < 2) USAGE(argv[0]);

    return 0;
}