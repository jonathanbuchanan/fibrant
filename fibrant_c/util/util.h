#ifndef UTIL_H
#define UTIL_H

#include <stddef.h>
#include <stdlib.h>

/* --- Memory --- */
/* Allocates memory. */
#define FIBRANT_NEW(T) ((T *)malloc(sizeof(T)))

/* Frees memory. */
#define FIBRANT_FREE(x) (free(x))

/* TODO: Custom allocators? */


/* --- Vectors --- */

/* The factor to increase vector capacity by when allocating more memory. */
#define FIBRANT_VEC_GROWTH_FACTOR 2

/* The type of a vector containing elements of type `T`. */
#define FIBRANT_VEC(T) \
  struct { \
    size_t capacity; \
    size_t length; \
    T *data; \
  }

/* Helper function for `FIBRANT_VEC_INIT`. */
int __Fibrant_vec_init(size_t *length, size_t *capacity, void **data,
    size_t data_size);

/* Initializes a vector. Evaluates to `0` on success or `1` otherwise. */
#define FIBRANT_VEC_INIT(vec) \
  __Fibrant_vec_init

/* Helper function for `FIBRANT_VEC_GET`. */
void * __Fibrant_vec_get(size_t length, size_t size, size_t index, void *data);

/* Accesses an element of a vector. If the index is out of range, evaluates to
 *   `NULL`. */
#define FIBRANT_VEC_GET(vec, i) \
  ((typeof(vec.data))__Fibrant_vec_get(vec.length, sizeof(*vec.data), i, \
    vec.data))

#endif