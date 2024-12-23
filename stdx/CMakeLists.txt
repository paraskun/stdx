file(GLOB SRC src/*.c src/*/*.c)

add_library(stdx ${SRC})

target_include_directories(stdx PUBLIC include/)
target_link_directories(stdx PUBLIC include/)

if (OPENMP_FOUND)
  target_link_libraries(stdx PUBLIC OpenMP::OpenMP_C)
endif()

add_executable(test_cut test/test_cut.c)
add_executable(test_pque test/test_pque.c)
add_executable(test_fun test/test_fun.c)

target_link_libraries(test_cut stdx munit)
target_link_libraries(test_pque stdx munit)
target_link_libraries(test_fun stdx munit)

add_test(
  NAME test_cut
  COMMAND test_cut
)

add_test(
  NAME test_pque
  COMMAND test_pque
)

add_test(
  NAME test_fun
  COMMAND test_fun
)
