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

#endif // BASICHASHMAP
