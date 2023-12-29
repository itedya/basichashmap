#ifndef BASICHASHMAP
#define BASICHASHMAP

#define BASICHASHMAP_SUCCESS 0
#define BASICHASHMAP_MEMORY_ERROR -1

struct basichashmap_s;

// Initializes hashmap
//
// Returns:
//  BASICHASHMAP_MEMORY_ERROR   - when dynamic allocation failed
//  BASICHASHMAP_SUCCESS        - when everything is ok
int basichashmap_init(struct basichashmap_s **hashmap);

/*
 * Frees the hashmap
 *
 * Params:
 *  hashmap                 - Pointer to hashmap struct.
 *  deallocation_function   - Function that will be run against every existing hashmap item for deallocation purposes. If provided null (for ex. because elements are on stack), function execution will be skipped.
 *
 * Returns:
 *  BASICHASHMAP_SUCCESS        - when everything went ok
 *  BASICHASHMAP_MEMORY ERROR   - when provided hashmap is NULL or if error inside the function occured
*/
int basichashmap_free(struct basichashmap_s *hashmap, void (* deallocation_function)(void *item));

#endif // BASICHASHMAP
