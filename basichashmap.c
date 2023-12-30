#include "basichashmap.h"
#include <stdlib.h>
#include <basicvector.h>
#include <string.h>

struct basichashmap_s {
    struct basicvector_s *vector;
};

struct basichashmap_entry_s {
    char *index;
    void *value;
};

// see usage of this struct in basichashmap_free for explanation
struct deallocation_user_data_s {
    void (*deallocation_function)(char *index, void *item, void *user_data);
    void *user_data;
};

void basichashmap_entry_s_deallocation_function(void *vector_item, void *user_data) {
    struct deallocation_user_data_s *deallocation_user_data = (struct deallocation_user_data_s *) user_data;
    struct basichashmap_entry_s *hashmap_entry = (struct basichashmap_entry_s *) vector_item;

    deallocation_user_data->deallocation_function(hashmap_entry->index, hashmap_entry->value, user_data);

    free(hashmap_entry->index);

    free(hashmap_entry);
}

int basichashmap_init(struct basichashmap_s **hashmap) {
    struct basichashmap_s *new_hashmap = malloc(sizeof(struct basichashmap_s));

    if (new_hashmap == NULL) {
        return BASICHASHMAP_MEMORY_ERROR;
    }

    if (basicvector_init(&new_hashmap->vector) != BASICVECTOR_SUCCESS) {
        free(new_hashmap);
        return BASICHASHMAP_MEMORY_ERROR;
    }

    *hashmap = new_hashmap;

    return BASICHASHMAP_SUCCESS;
}

bool basicvector_get_search_function(void *item, void *user_data) {
    struct basichashmap_entry_s *entry = (struct basichashmap_entry_s *) item;
    char *index = (char *) user_data;

    return strcmp(index, entry->index) == 0;
}

int basichashmap_get(struct basichashmap_s *hashmap, char *index, void **result) {
    if (hashmap == NULL) return BASICHASHMAP_MEMORY_ERROR;
    if (index == NULL || result == NULL) return BASICHASHMAP_INVALID_ARGUMENT;

    struct basichashmap_entry_s *entry_result;

    int status = basicvector_find(hashmap->vector, (void **) &entry_result, basicvector_get_search_function, index);

    switch (status) {
        case BASICVECTOR_SUCCESS:
            *result = entry_result->value;
            return BASICHASHMAP_SUCCESS;
        case BASICVECTOR_ITEM_NOT_FOUND:
            return BASICHASHMAP_ITEM_NOT_FOUND;
        default:
            return BASICHASHMAP_MEMORY_ERROR;
    };
}

bool basichashmap_remove_by_index_search_callback(
    void *item,
    void *user_data
) {
    char *searched_index = (char*) user_data;
    struct basichashmap_entry_s *entry = (struct basichashmap_entry_s *) item;

    return strcmp(entry->index, searched_index) == 0;
}

int basichashmap_remove_by_index(
    struct basichashmap_s *hashmap,
    char *index,
    void (*deallocation_function)(char *index, void *value, void *user_data),
    void *user_data
) {
    if (hashmap == NULL) return BASICHASHMAP_MEMORY_ERROR;
    if (index == NULL) return BASICHASHMAP_INVALID_ARGUMENT;

    int result;

    int status = basicvector_find_index(hashmap->vector, &result, basichashmap_remove_by_index_search_callback, index);
    if (status == BASICVECTOR_ITEM_NOT_FOUND) {
        return BASICHASHMAP_ITEM_NOT_FOUND;
    } else if (status != BASICVECTOR_SUCCESS) {
        return BASICHASHMAP_MEMORY_ERROR;
    }

    struct deallocation_user_data_s deallocation_user_data = { deallocation_function, user_data };

    basicvector_remove(hashmap->vector, result, basichashmap_entry_s_deallocation_function, &deallocation_user_data);

    return BASICHASHMAP_SUCCESS;
}

int basichashmap_set(
    struct basichashmap_s *hashmap, 
    char *index, 
    void *value, 
    void (*deallocation_function)(char *index, void *value, void *user_data), 
    void *user_data
) {
    if (hashmap == NULL) {
        return BASICHASHMAP_MEMORY_ERROR;
    }

    if (index == NULL) {
        return BASICHASHMAP_INVALID_ARGUMENT;
    }

    int remove_status = basichashmap_remove_by_index(hashmap, index, deallocation_function, user_data);

    if (remove_status != BASICHASHMAP_SUCCESS && remove_status != BASICHASHMAP_ITEM_NOT_FOUND) {
        return remove_status;
    }

    struct basichashmap_entry_s *entry = malloc(sizeof(struct basichashmap_entry_s));

    char *own_index = malloc(sizeof(char) * (strlen(index) + 1));
    strcpy(own_index, index);
    entry->index = own_index;
    entry->value = value;

    basicvector_push(hashmap->vector, entry);

    return BASICHASHMAP_SUCCESS;
}

int basichashmap_free(struct basichashmap_s *hashmap, void (* deallocation_function)(char *index, void *item, void *user_data), void *user_data) {
    if (hashmap == NULL) {
        return BASICHASHMAP_MEMORY_ERROR;
    }

    // Type of deallocation function in basicvector library does not correspond to one that we have. Because of that, there is a struct that is only for passing data to compatible deallocation function and then from that data we can execute proper callback (see basichashmap_entry_s_deallocation_function).
    struct deallocation_user_data_s deallocation_user_data = { deallocation_function, user_data };

    basicvector_free(hashmap->vector, basichashmap_entry_s_deallocation_function, &deallocation_user_data);

    return BASICHASHMAP_SUCCESS;
}
