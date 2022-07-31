#include "util.h"

int __Fibrant_vec_init(size_t *capacity, size_t *length, void **data,
    size_t data_size) {
  if (NULL == capacity)
    return 1;
  if (NULL == length)
    return 1;
  if (NULL == data)
    return 1;
  *data = FIBRANT_MALLOC(data_size);
  if (NULL == *data)
    return 1;
  *capacity = 1;
  *length = 0;
  return 0;
}

void __Fibrant_vec_free(size_t *capacity, size_t *length, void **data) {
  if (NULL != capacity)
    *capacity = 0;
  if (NULL != length)
    *length = 0;
  if (NULL != data) {
    free(*data);
    *data = NULL;
  }
}

void * __Fibrant_vec_get(size_t length, size_t size, size_t index, void *data) {
  if (NULL == data)
    return NULL;
  else if (index >= length)
    return NULL;
  else
    return &data[index * size];
}

int __Fibrant_vec_make_room(size_t *capacity, size_t *length, void **data,
    size_t data_size) {
  if (NULL == capacity)
    return 1;
  else if (NULL == length)
    return 1;
  else if (NULL == data)
    return 1;
  /* If we need more capacity, allocate it. */
  if (*length >= *capacity) {
    size_t new_capacity = FIBRANT_VEC_GROWTH_FACTOR * (*length);
    void *new_data;
    if (NULL == *data) {
      new_data = FIBRANT_MALLOC(data_size * new_capacity);
    } else {
      /* TODO: wrapper macro around realloc in case of a custom allocator. */
      new_data = realloc(*data, data_size * new_capacity);
    }
    if (NULL == new_data)
      return 1;
    *data = new_data;
    *capacity = new_capacity;
  }
  *length += 1;
  return 0;
}
