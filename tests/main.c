#include "helpers.h"
#include "../basichashmap.h"
#include <stdio.h>
#include <stdlib.h>

void basichashmap_init_1__test_if_basichashmap_init_initializes_it() {
    struct basichashmap_s *hashmap;

    expect_status_success(basichashmap_init(&hashmap));
    
    expect_status_success(basichashmap_free(hashmap, NULL, NULL));

    pass("[basichashmap_init 1] initializes it");
}

void basichashmap_init_2__test_if_basichashmap_init_returns_memory_error_when_passed_null_as_hashmap() {
    expect_status(basichashmap_init(NULL), BASICHASHMAP_MEMORY_ERROR);

    pass("[basichashmap_init 2] returns memory error when passed null as hashmap");
}

void basichashmap_count_1__test_if_returns_memory_error_when_passed_hashmap_is_null() {
    int length;

    expect_status(basichashmap_count(NULL, &length), BASICHASHMAP_MEMORY_ERROR);
    
    pass("[basichashmap_count 1] returns memory error when passed hashmap is null");
}

void basichashmap_count_2__test_if_returns_invalid_argument_error_when_passed_length_ptr_is_null() {
    struct basichashmap_s *hashmap;

    expect_status_success(basichashmap_init(&hashmap));

    expect_status(basichashmap_count(hashmap, NULL), BASICHASHMAP_INVALID_ARGUMENT);

    expect_status_success(basichashmap_free(hashmap, NULL, NULL));
    
    pass("[basichashmap_count 2] returns invalid argument error when passed length ptr is null");
}

void basichashmap_count_3__test_if_returns_0_when_hashmap_does_not_have_any_items() {
    struct basichashmap_s *hashmap;

    expect_status_success(basichashmap_init(&hashmap));

    int length;

    expect_status_success(basichashmap_count(hashmap, &length));

    char *error_message = malloc(sizeof(char) * 256);
    sprintf(error_message, "Expected length to be 0, received %d.", length);
    assert(length == 0, error_message);
    free(error_message);

    expect_status_success(basichashmap_free(hashmap, NULL, NULL));
    
    pass("[basichashmap_count 3] returns 0 when hashmap does not have any items");
}

void basichashmap_count_4__test_if_returns_2_when_hashmap_has_two_items() {
    struct basichashmap_s *hashmap;

    expect_status_success(basichashmap_init(&hashmap));

    expect_status_success(basichashmap_set(hashmap, "first_item", NULL, NULL, NULL));

    expect_status_success(basichashmap_set(hashmap, "second_item", NULL, NULL, NULL));

    int length;

    expect_status_success(basichashmap_count(hashmap, &length));

    char *error_message = malloc(sizeof(char) * 256);
    sprintf(error_message, "Expected length to be 2, received %d.", length);
    assert(length == 2, error_message);
    free(error_message);

    expect_status_success(basichashmap_free(hashmap, NULL, NULL));

    printf("121\n");

    
    pass("[basichashmap_count 4] returns 2 when hashmap has two items");
}

int main() {
    basichashmap_init_1__test_if_basichashmap_init_initializes_it();
    basichashmap_init_2__test_if_basichashmap_init_returns_memory_error_when_passed_null_as_hashmap();

    basichashmap_count_1__test_if_returns_memory_error_when_passed_hashmap_is_null();
    basichashmap_count_2__test_if_returns_invalid_argument_error_when_passed_length_ptr_is_null();
    basichashmap_count_3__test_if_returns_0_when_hashmap_does_not_have_any_items();
    basichashmap_count_4__test_if_returns_2_when_hashmap_has_two_items();

    pass("All passed");

    return EXIT_SUCCESS;
}
