add_library(fibrant
  expr.c
)

target_link_libraries(fibrant util)
target_include_directories(fibrant
  PUBLIC ../util
)
