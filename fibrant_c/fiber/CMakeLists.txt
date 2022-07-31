add_executable(fiber
  main.c
)

target_link_libraries(fiber fibrant util)
target_include_directories(fiber
  PUBLIC ../
)
