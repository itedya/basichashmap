#include "basichashmap.h"
#include <stdlib.h>
#include <basicvector.h>

struct basichashmap_s {
    struct basicvector_s *vector;
};

struct basichashmap_entry_s {
    char *index;
    void *data;
};

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

// see usage of this struct in basichashmap_free for explanation
struct deallocation_user_data_basicvector_free_s {
    void (*deallocation_function)(void *index, void *item, void *user_data);
    void *user_data;
};

void basichashmap_entry_s_deallocation_function(void *vector_item, void *user_data) {
    struct deallocation_user_data_basicvector_free_s *deallocation_user_data = (struct deallocation_user_data_basicvector_free_s *) user_data;
    struct basichashmap_entry_s *hashmap_entry = (struct basichashmap_entry_s *) vector_item;

    deallocation_user_data->deallocation_function(hashmap_entry->index, hashmap_entry->data, user_data);

    free(hashmap_entry->index);

    free(hashmap_entry);
}

int basichashmap_free(struct basichashmap_s *hashmap, void (* deallocation_function)(void *index, void *item, void *user_data), void *user_data) {
    if (hashmap == NULL) {
        return BASICHASHMAP_MEMORY_ERROR;
    }

    // Type of deallocation function in basicvector library does not correspond to one that we have. Because of that, there is a struct that is only for passing data to compatible deallocation function and then from that data we can execute proper callback (see basichashmap_entry_s_deallocation_function).
    struct deallocation_user_data_basicvector_free_s deallocation_user_data = { deallocation_function, user_data };

    basicvector_free(hashmap->vector, basichashmap_entry_s_deallocation_function, &deallocation_user_data);

    return BASICHASHMAP_SUCCESS;
}
