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

    return BASICHASHMAP_SUCCESS;
}

void basichashmap_entry_s_deallocation_function(void *entry) {
    struct basichashmap_entry_s *hashmap_entry = (struct basichashmap_entry_s *) entry;

    free(hashmap_entry->index);

    free(hashmap_entry);
}

int basichashmap_free(struct basichashmap_s *hashmap, void (* deallocation_function)(void *item)) {
    if (hashmap == NULL) {
        return BASICHASHMAP_MEMORY_ERROR;
    }

    int length;

    if (basicvector_length(hashmap->vector, &length) != BASICVECTOR_SUCCESS) {
        return BASICHASHMAP_MEMORY_ERROR;
    }

    if (deallocation_function != NULL) {
        for (int i = 0; i < length; i++) {
            struct basichashmap_entry_s *entry;

            if (basicvector_get(hashmap->vector, i, (void **) &entry) != BASICVECTOR_SUCCESS) {
                return BASICHASHMAP_MEMORY_ERROR;
            }

            deallocation_function(entry->data);
        }
    }

    basicvector_free(hashmap->vector, basichashmap_entry_s_deallocation_function);

    return BASICHASHMAP_SUCCESS;
}
