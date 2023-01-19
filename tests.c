#include "da_tests.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USAGE(filename)                                         \
    do                                                          \
    {                                                           \
        fprintf(stderr, "Usage: %s <test name>\n", (filename)); \
        exit(1);                                                \
    } while (0)

typedef struct {
    char *name;
    bool (*func)(void);
} Test;

Test tests[] = {

    {"test_create", test_create},
    {"test_destroy", test_destroy},
    {"test_clear", test_clear},
    // NULL_test
    {0, NULL},
};

int main(int argc, char **argv) {
    if (argc < 2) USAGE(argv[0]);
    int ret = -1;

    for (const Test *test = tests; test->name && test->func; test++)
    {
        if (!strcmp(argv[1], test->name))
        {
            ret = (int)test->func();
            break;
        }
    }

    switch (ret)
    {
    case -1: printf("test \"%s\" not found\n", argv[1]); return EXIT_FAILURE;
    case 0: printf("test \"%s\" finished : FAILURE\n", argv[1]); return EXIT_FAILURE;
    case 1: printf("test \"%s\" finished : SUCCESS\n", argv[1]); return EXIT_SUCCESS;
    default: return EXIT_FAILURE;
    }
}