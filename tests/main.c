#include "helpers.h"
#include "../basichashmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    pass("[basichashmap_count 4] returns 2 when hashmap has two items");
}

void basichashmap_set_1__test_if_returns_memory_error_when_passed_hashmap_is_null() {
    expect_status(basichashmap_set(NULL, "helloworld", NULL, NULL, NULL), BASICHASHMAP_MEMORY_ERROR);

    pass("[basichashmap_set 1] returns memory error when passed hashmap is null");
}

void basichashmap_set_2__test_if_returns_invalid_argument_error_when_passed_index_is_null() {
    struct basichashmap_s *hashmap;

    expect_status_success(basichashmap_init(&hashmap));

    expect_status(basichashmap_set(hashmap, NULL, NULL, NULL, NULL), BASICHASHMAP_INVALID_ARGUMENT);

    expect_status_success(basichashmap_free(hashmap, NULL, NULL));

    pass("[basichashmap_set 2] returns invalid argument error when passed index is null");
}

bool basichashmap_set_3__FLAG_DEALLOCATION_FUNCTION_EXECUTED = false;

void basichashmap_set_3__deallocation_function(char *index, void *value, void *user_data) {
    // silence the compiler
    index = index;
    value = value;
    user_data = user_data;

    basichashmap_set_3__FLAG_DEALLOCATION_FUNCTION_EXECUTED = true;
}

// does: return success
// does not: execute deallocation function
// does: set item successfully
//
// when: given item does not exist
void basichashmap_set_3__test_if_returns_success_and_does_not_execute_deallocation_function_and_sets_item_if_item_with_given_index_does_not_exist() {
    struct basichashmap_s *hashmap;

    expect_status_success(basichashmap_init(&hashmap));

    int item = 66;

    // when: given item does not exist
    // does: return success
    expect_status_success(basichashmap_set(hashmap, "helloworld2", &item, basichashmap_set_3__deallocation_function, NULL));

    // does: set item successfully
    int *received_item_ptr;
    expect_status_success(basichashmap_get(hashmap, "helloworld2", (void **) &received_item_ptr));
    assert(received_item_ptr == &item, "Received item ptr is not the same as item ptr");

    // does not: execute deallocation function
    assert(basichashmap_set_3__FLAG_DEALLOCATION_FUNCTION_EXECUTED == false, "Deallocation function was executed, but it shouldn't be.");

    expect_status_success(basichashmap_free(hashmap, NULL, NULL));

    pass("[basichashmap_set 3] returns success, does not execute deallocation function and sets item if item with given index does not exist");
}

/*
 * Does:
 *  - Return success
 *  - Does not execute deallocation function
 *  - Sets item successfully
 *
 * When:
 *  - Deallocation function is null
 *  - Given index exists
 */
void basichashmap_set_4__test_if_returns_success_and_does_not_execute_deallocation_function_when_it_is_null_and_item_with_given_index_exists() {
    // prepare
    struct basichashmap_s *hashmap;

    expect_status_success(basichashmap_init(&hashmap));

    // when: given index exists
    int item = 66;
    expect_status_success(basichashmap_set(hashmap, "helloworld", &item, basichashmap_set_3__deallocation_function, NULL));

    int *received_item_ptr;
    expect_status_success(basichashmap_get(hashmap, "helloworld", (void **) &received_item_ptr));
    assert(received_item_ptr == &item, "Received item ptr is not the same as item ptr");

    int next_item = 123;

    // when: given index exists
    expect_status_success(basichashmap_set(hashmap, "helloworld2", &next_item, NULL, NULL));

    expect_status_success(basichashmap_get(hashmap, "helloworld2", (void **) &received_item_ptr));

    assert(received_item_ptr == &next_item, "Received item ptr is not the same as item ptr");

    // actual work

    // when: deallocation function is null
    // retruns success
    // does not execute deallocation function
    int third_item = -923;
    expect_status_success(basichashmap_set(hashmap, "helloworld2", &third_item, NULL, NULL));

    // checking 
    expect_status_success(basichashmap_get(hashmap, "helloworld", (void **) &received_item_ptr));
    assert(received_item_ptr == &item, "received_item_ptr is not an item address");

    // sets item successfully
    expect_status_success(basichashmap_get(hashmap, "helloworld2", (void **) &received_item_ptr));
    assert(received_item_ptr == &third_item, "received_item_ptr is not a third_item address");

    expect_status_success(basichashmap_free(hashmap, NULL, NULL));

    pass("[basichashmap_set 4] returns success and does not execute deallocation function when it is null and item with given index exists");
}

struct basichashmap_set_5_DEALLOCATION_FUNCTION_user_data_s {
    char *touched_index;
    void *touched_value;
    void *received_user_data;
};

typedef struct basichashmap_set_5_DEALLOCATION_FUNCTION_user_data_s bs5_DFud_s;

void basichashmap_set_5__DEALLOCATION_FUNCTION(char *index, void *value, void *user_data) {
    struct basichashmap_set_5_DEALLOCATION_FUNCTION_user_data_s *checks = (struct basichashmap_set_5_DEALLOCATION_FUNCTION_user_data_s *) user_data;

    checks->touched_index = malloc(sizeof(char) * (strlen(index) + 1)); 
    strcpy(checks->touched_index, index);

    checks->touched_value = value;
    checks->received_user_data = user_data;
}

// Does:
//  - Return success
//  - Sets item
//  - Executes deallocation function
//  - Executes deallocation function with correct args
//
// When:
//  - Item already exists
void basichashmap_set_5__test_if_returns_success_and_sets_item_and_executes_deallocation_function_with_correct_args_when_item_already_exists() {
    // initialize
    struct basichashmap_s *hashmap;

    expect_status_success(basichashmap_init(&hashmap));

    // adds two items on startup
    
    int item1 = 109283;
    int item2 = 1832;
    
    expect_status_success(basichashmap_set(hashmap, "first_item", &item1, NULL, NULL));
    expect_status_success(basichashmap_set(hashmap, "second_item", &item2, NULL, NULL));

    // actual work
    int item3 = 18239803;

    struct basichashmap_set_5_DEALLOCATION_FUNCTION_user_data_s *user_data = malloc(sizeof(struct basichashmap_set_5_DEALLOCATION_FUNCTION_user_data_s));

    // does: return success
    expect_status_success(basichashmap_set(hashmap, "second_item", &item3, basichashmap_set_5__DEALLOCATION_FUNCTION, user_data));
 
    int *received_ptr;

    expect_status_success(basichashmap_get(hashmap, "first_item", (void **) &received_ptr));
    assert(received_ptr == &item1, "received_ptr is not equal to item1 address");

    // does: set item
    expect_status_success(basichashmap_get(hashmap, "second_item", (void **) &received_ptr));
    assert(received_ptr == &item3, "received_ptr is not equal to item3 address");

    // does: execute deallocation function
    // does: execute deallocation function with correct args
    assert(strcmp("second_item", user_data->touched_index) == 0, "Deallocation function has been run with wrong index");
    assert(user_data->touched_value == &item2, "Deallocation function has been run with wrong value");
    assert(user_data->received_user_data == user_data, "Deallocation function has been run with wrong user data");


    expect_status_success(basichashmap_free(hashmap, NULL, NULL));
    
    pass("[basichashmap_set 5] returns success and sets item and executes deallocation function with correct args when item already exists");
}

void basichashmap_get_1__test_if_returns_memory_error_when_hashmap_is_null() {
    int *result;
    
    expect_status(basichashmap_get(NULL, "something", (void **) &result), BASICHASHMAP_MEMORY_ERROR);
    
    pass("[basichashmap_get 1] returns memory error hwen hashmap is null");
}

 void basichashmap_get_2__test_if_returns_invalid_argument_when_index_is_null() {
    struct basichashmap_s *hashmap;

    expect_status_success(basichashmap_init(&hashmap));

    int *result;

    expect_status(basichashmap_get(hashmap, NULL, (void **) &result), BASICHASHMAP_INVALID_ARGUMENT);

    expect_status_success(basichashmap_free(hashmap, NULL, NULL));

    pass("[basichashmap_get 2] returns invalid argument when index is null");
}

void basichashmap_get_3__test_if_returns_invalid_argument_when_result_is_null() {
    struct basichashmap_s *hashmap;

    expect_status_success(basichashmap_init(&hashmap));

    expect_status(basichashmap_get(hashmap, "helloworld", NULL), BASICHASHMAP_INVALID_ARGUMENT);

    expect_status_success(basichashmap_free(hashmap, NULL, NULL));

    pass("[basichashmap_get 3] returns invalid argument when result is null");
}

void basichashmap_get_4__test_if_returns_status_success_with_valid_item_when_item_exists() {
    struct basichashmap_s *hashmap;

    expect_status_success(basichashmap_init(&hashmap));

    int item1 = 129803;
    int item2 = 7328;

    expect_status_success(basichashmap_set(hashmap, "first_item", &item1, NULL, NULL));
    expect_status_success(basichashmap_set(hashmap, "second_item", &item2, NULL, NULL));

    int *result;

    expect_status_success(basichashmap_get(hashmap, "first_item", (void **) &result));
    assert(result == &item1, "result ptr is not equal to item1 var address");

    expect_status_success(basichashmap_get(hashmap, "second_item", (void **) &result));
    assert(result == &item2, "result ptr is not equal to item2 var address");

    expect_status_success(basichashmap_free(hashmap, NULL, NULL));

    pass("[basichashmap_get 4] returns status success with valid item when item exists");
}

void basichashmap_get_5__test_if_returns_status_item_not_found_when_item_does_not_exist() {
    struct basichashmap_s *hashmap;

    expect_status_success(basichashmap_init(&hashmap));
    
    expect_status_success(basichashmap_set(hashmap, "first_item", NULL, NULL, NULL));

    int *result;
    expect_status(basichashmap_get(hashmap, "somenonexistingitem", (void **) &result), BASICHASHMAP_ITEM_NOT_FOUND);

    expect_status_success(basichashmap_free(hashmap, NULL, NULL));

    pass("[basichashmap_get 5] returns status item not found when item does not exist");
}

int main() {
    basichashmap_init_1__test_if_basichashmap_init_initializes_it();
    basichashmap_init_2__test_if_basichashmap_init_returns_memory_error_when_passed_null_as_hashmap();

    basichashmap_count_1__test_if_returns_memory_error_when_passed_hashmap_is_null();
    basichashmap_count_2__test_if_returns_invalid_argument_error_when_passed_length_ptr_is_null();
    basichashmap_count_3__test_if_returns_0_when_hashmap_does_not_have_any_items();
    basichashmap_count_4__test_if_returns_2_when_hashmap_has_two_items();

    basichashmap_set_1__test_if_returns_memory_error_when_passed_hashmap_is_null();
    basichashmap_set_2__test_if_returns_invalid_argument_error_when_passed_index_is_null();
    basichashmap_set_3__test_if_returns_success_and_does_not_execute_deallocation_function_and_sets_item_if_item_with_given_index_does_not_exist();
    basichashmap_set_4__test_if_returns_success_and_does_not_execute_deallocation_function_when_it_is_null_and_item_with_given_index_exists();
    basichashmap_set_5__test_if_returns_success_and_sets_item_and_executes_deallocation_function_with_correct_args_when_item_already_exists();

    basichashmap_get_1__test_if_returns_memory_error_when_hashmap_is_null();
    basichashmap_get_2__test_if_returns_invalid_argument_when_index_is_null();
    basichashmap_get_3__test_if_returns_invalid_argument_when_result_is_null();
    basichashmap_get_4__test_if_returns_status_success_with_valid_item_when_item_exists();
    basichashmap_get_5__test_if_returns_status_item_not_found_when_item_does_not_exist();

    pass("All passed");

    return EXIT_SUCCESS;
}
