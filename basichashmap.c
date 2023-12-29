#include "basichashmap.h"
#include <stdlib.h>
#include <basicvector.h>

struct basichashmap_s {
    struct basicvector_s *vector;
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
