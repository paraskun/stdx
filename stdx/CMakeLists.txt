file(GLOB SRC src/**/*.c)

add_library(stdx ${SRC})

target_include_directories(stdx PUBLIC include/)
