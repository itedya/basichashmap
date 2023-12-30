#include "helpers.h"
#include "../basichashmap.h"
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

int main() {
    basichashmap_init_1__test_if_basichashmap_init_initializes_it();
    basichashmap_init_2__test_if_basichashmap_init_returns_memory_error_when_passed_null_as_hashmap();

    pass("All passed");

    return EXIT_SUCCESS;
}
