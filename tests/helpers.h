#ifndef BASICHASHMAP_TEST_HELPERS
#define BASICHASHMAP_TEST_HELPERS

#include <stdbool.h>

void assert(bool result, char *message);

void pass(char *message);

char *status_to_string(int status);

char *bool_to_string(bool payload);

void expect_status(int received, int expected);

void expect_status_success(int status);


#endif // BASICHASHMAP_TEST_HELPERS
