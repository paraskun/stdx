set(SRC
  src/cmp.c
  src/cut/icut.c
  src/cut/dcut.c
  src/cut/pcut.c
  src/log/ilog.c
  src/pque/pque.h
  src/pque/ipque.c
  src/pque/dpque.c
  src/pque/ppque.c
)

add_library(stdx ${SRC})

target_include_directories(stdx PUBLIC include/)
target_link_directories(stdx PUBLIC include/)

add_executable(test_cut test/test_cut.c)
add_executable(test_pque test/test_pque.c)

target_link_libraries(test_cut stdx munit)
target_link_libraries(test_pque stdx munit)

add_test(NAME test_cut COMMAND test_cut)
add_test(NAME test_pque COMMAND test_pque)

