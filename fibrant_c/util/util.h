#ifndef UTIL_H
#define UTIL_H

#include <stddef.h>
#include <stdlib.h>

/* --- Memory --- */
/* Allocates memory. */
#define FIBRANT_MALLOC(n) malloc(n)

/* Allocates memory for a type. */
#define FIBRANT_NEW(T) ((T *)FIBRANT_MALLOC(sizeof(T)))

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

/* Initializes a vector. Evaluates to `0` on success or `1` otherwise. */
#define FIBRANT_VEC_INIT(vec) \
    __Fibrant_vec_init(&vec.capacity, &vec.length, (void **)&vec.data, \
        sizeof(*vec.data))

/* Frees a vector. */
#define FIBRANT_VEC_FREE(vec) \
    __Fibrant_vec_free(&vec.capacity, &vec.length, (void **)&vec.data)

/* Accesses an element of a vector (as a pointer). If the index is out of range,
 * evaluates to `NULL`. */
#define FIBRANT_VEC_GET(vec, i) \
    ((typeof(vec.data))__Fibrant_vec_get(vec.length, sizeof(*vec.data), i, \
      (void **)vec.data))

/* Accesses an element of a vector (by value). If the index is out of range,
 * results in dereferencing `NULL` */
#define FIBRANT_VEC_GET2(vec, i) \
    (*((typeof(vec.data))__Fibrant_vec_get(vec.length, sizeof(*vec.data), i, \
      (void **)vec.data)))

/* Evaluates to the length of a vector. */
#define FIBRANT_VEC_LEN(vec) \
    (vec.length)

/* Appends an element to a vector. Returns `0` on success and `1` otherwise. */
#define FIBRANT_VEC_PUSH(vec, x) \
    ((0 == __Fibrant_vec_make_room(&vec.capacity, &vec.length, \
        (void **)&vec.data, sizeof(*vec.data))) \
      ? (*FIBRANT_VEC_GET(vec, FIBRANT_VEC_LEN(vec) - 1) = x, 0) \
      : 1)




/* Helper function for `FIBRANT_VEC_INIT`. */
int __Fibrant_vec_init(size_t *capacity, size_t *length, void **data,
    size_t data_size);

/* Helper function for `FIBRANT_VEC_FREE`. */
void __Fibrant_vec_free(size_t *capacity, size_t *length, void **data);

/* Helper function for `FIBRANT_VEC_GET`. */
void * __Fibrant_vec_get(size_t length, size_t size, size_t index, void *data);

/* Helper function for `FIBRANT_VEC_PUSH. */
int __Fibrant_vec_make_room(size_t *capacity, size_t *length, void **data,
    size_t data_size);

#endif