#ifndef BASICHASHMAP
#define BASICHASHMAP

#define BASICHASHMAP_SUCCESS 0
#define BASICHASHMAP_MEMORY_ERROR -1
#define BASICHASHMAP_INVALID_ARGUMENT -2
#define BASICHASHMAP_ITEM_NOT_FOUND -3

struct basichashmap_s;

/* 
 * Initializes hashmap
 *
 * Params:
 *  hashmap - Pointer to hashmap struct
 *
 * Returns:
 *  BASICHASHMAP_MEMORY_ERROR   - when dynamic allocation failed
 *  BASICHASHMAP_SUCCESS        - when everything went ok 
*/
int basichashmap_init(struct basichashmap_s **hashmap);

/*
 * Get item from the hashmap by index
 *
 * Params:
 *  hashmap - Pointer to hashmap instance
 *  index   - Index of wanted item
 *  result  - Pointer that underneath will have a pointer to item value
 *
 * Returns:
 *  BASICHASHMAP_SUCCESS            - When everything went ok
 *  BASICHASHMAP_MEMORY_ERROR       - When hashmap is NULL
 *  BASiCHASHMAP_INVALID_ARGUMENT   - When result is NULL or when index is NULL
 */
int basichashmap_get(struct basichashmap_s *hashmap, char *index, void **result);

/*
 * Set item in hashmap
 *
 * Params:
 *  hashmap                 - Pointer to hashmap instance
 *  index                   - Index of new item (this value will be copied, memory management is done internally)
 *  value                   - Pointer of new item value
 *  deallocation_function   - Function that is executed when item of given index already exists and it needs to be deallocated before the new item is allocated. First parameter of the function is index, second the value of old item and third is value of user_data parameter (see last parameter of basichashmap_set function)
 *  user_data               - Pointer with context data that is later passed to deallocation_function
 *
 * Returns:
 *  BASICHASHMAP_SUCCESS            - When everything went ok
 *  BASICHASHMAP_MEMORY_ERROR       - When passed hashmap is NULL or memory error occured (for example could not allocate memory for new item)
 *  BASICHASHMAP_INVALID_ARGUMENT   - When passed index is NULL
 */
int basichashmap_set(struct basichashmap_s *hashmap, char *index, void *value, void (*deallocation_function)(char *index, void *value, void *user_data), void *user_data);

/*
 * Removes item from hashmap by index
 *
 * Params:
 *  hashmap                 - Pointer to hashmap instance
 *  index                   - Index of item item
 *  deallocation_function   - Function that is executed when item needs to be deallocated. First parameter of the function is index, second is the value of item and third is value of user_data parameter (see last parameter of basichashmap_remove_by_index function)
 *  user_data               - Pointer with context data that is later passed to deallocation_function
 *
 * Returns:
 *  BASICHASHMAP_SUCCESS            - When everything went ok
 *  BASICHASHMAP_MEMORY_ERROR       - When hashmap is null or if something internally went wrong
 *  BASICHASHMAP_INVALID_ARGUMENT   - When index is null
 *  BASICHASHMAP_ITEM_NOT_FOUND     - When value with given index does not exist
 */
int basichashmap_remove_by_index(
    struct basichashmap_s *hashmap,
    char *index,
    void (*deallocation_function)(char *index, void *value, void *user_data),
    void *user_data
);

/*
 * Frees the hashmap from memory
 *
 * Params:
 *  hashmap                 - Pointer to hashmap struct.
 *  deallocation_function   - Function that will be run against every existing hashmap item for deallocation purposes. If provided null (for ex. because elements are on stack), function execution will be skipped.
 *  user_data               - Data that will be passed to deallocation function. If you need any context data in deallocation function, this is your saviour.
 *
 * Returns:
 *  BASICHASHMAP_SUCCESS        - when everything went ok
 *  BASICHASHMAP_MEMORY ERROR   - when provided hashmap is NULL or if error inside the function occured
*/
int basichashmap_free(struct basichashmap_s *hashmap, void (* deallocation_function)(char *index, void *item, void *user_data), void *user_data);

#endif // BASICHASHMAP
