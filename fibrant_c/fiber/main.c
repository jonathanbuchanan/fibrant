#include <stdio.h>
#include <util/util.h>

int main(int argc, char **argv) {
  FIBRANT_VEC(int) test_vec;

  if (1 == FIBRANT_VEC_INIT(test_vec)) {
    printf("err\n");
    return 1;
  }

  printf("length: %zu\n", FIBRANT_VEC_LEN(test_vec));

  if (1 == FIBRANT_VEC_PUSH(test_vec, 42)) {
    printf("err\n");
    return 1;
  }

  printf("length: %zu\n", FIBRANT_VEC_LEN(test_vec));

  for (size_t i = 0; i < FIBRANT_VEC_LEN(test_vec); ++i) {
    printf("found %d\n", FIBRANT_VEC_GET2(test_vec, i));
  }

  FIBRANT_VEC_FREE(test_vec);
  printf("length: %zu\n", FIBRANT_VEC_LEN(test_vec));

  return 0;
}
