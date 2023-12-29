#include "basichashmap.h"
#include <stdlib.h>
#include <basicvector.h>

struct basichashmap_s {
    struct basicvector_s *vector;
};

int basichashmap_init(struct basichashmap_s **hashmap) {
    *hashmap = malloc(sizeof(struct basichashmap_s));
    
    if (*hashmap == NULL) {
        return BASICHASHMAP_MEMORY_ERROR;
    }

    return BASICHASHMAP_SUCCESS;
}
