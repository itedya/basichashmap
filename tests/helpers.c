#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include "../basichashmap.h"

void assert(bool result, char *message) {
    if (!result) {
        printf("[FAIL] %s\n", message);
        exit(EXIT_FAILURE);
    }
}

void pass(char *message) {
    printf("[PASS] %s\n", message);
}

char *status_to_string(int status) {
    switch (status) {
        case BASICHASHMAP_SUCCESS:
            return "BASICHASHMAP_SUCCESS";
        case BASICHASHMAP_MEMORY_ERROR:
            return "BASICHASHMAP_MEMORY_ERROR";
        case BASICHASHMAP_ITEM_NOT_FOUND:
            return "BASICHASHMAP_ITEM_NOT_FOUND";
        case BASICHASHMAP_INVALID_ARGUMENT:
            return "BASICHASHMAP_INVALID_ARGUMENT";
        default:
            return "Unknown status";
    }
}

char *bool_to_string(bool payload) {
    return payload ? "true" : "false";
}

void expect_status(int received, int expected) {
    char *error_message = malloc(sizeof(char) * 256);
    sprintf(error_message, "Expected status to be %s, received %s instead", status_to_string(expected), status_to_string(received));
    assert(received == expected, error_message);
    free(error_message);
}

void expect_status_success(int status) {
    char *returned_status = status_to_string(status);

    char *error_message = malloc(sizeof(char) * 256);
    sprintf(error_message, "Expected status to be BASICVECTOR_SUCCESS, received %s", returned_status);
    assert(status == BASICHASHMAP_SUCCESS, error_message);

    free(error_message);
}
