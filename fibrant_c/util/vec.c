#include "util.h"

void * __Fibrant_vec_get(size_t length, size_t size, size_t index, void *data) {
  if (NULL == data)
    return NULL;
  else if (index >= length)
    return NULL;
  else
    return &data[index * size];
}
