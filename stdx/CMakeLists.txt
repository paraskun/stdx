file(GLOB SRC src/*.c src/*/*.c)

add_library(stdx ${SRC})

target_include_directories(stdx PUBLIC include/)

add_executable(test_cut test/test_cut.c)

target_link_libraries(test_cut stdx munit)

add_test(
  NAME test_cut
  COMMAND test_cut
)
