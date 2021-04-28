add_subdirectory(platform)
add_subdirectory(util)

set(main_src 
    main.c 
    server.c
    smtp.c
)
add_executable(ngmail ${main_src})

# Refatorar isso no FIND
# Try to find the header
FIND_PATH(LIBUV_INCLUDE_DIR NAMES uv.h)
# Try to find the library
FIND_LIBRARY(LIBUV_LIBRARY NAMES uv libuv)

target_link_libraries(ngmail platform util)
target_link_libraries(ngmail ${LIBUV_LIBRARY})