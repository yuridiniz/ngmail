include_directories("${CMAKE_SOURCE_DIR}/src/")

add_subdirectory(platform)
add_subdirectory(util)
add_subdirectory(smtp)
add_subdirectory(http)

set(main_src 
    main.c 
    server.c
)

add_executable(ngmail ${main_src})

# Refatorar isso no FIND
# Try to find the header
FIND_PATH(LIBUV_INCLUDE_DIR NAMES uv.h)
# Try to find the library
FIND_LIBRARY(LIBUV_LIBRARY NAMES uv libuv)



# Refatorar isso no FIND
# Try to find the header
FIND_PATH(libpthread_dir NAMES pthread.h)
# Try to find the library
FIND_LIBRARY(libpthread_lib NAMES pthread)

target_link_libraries(ngmail platform)
target_link_libraries(ngmail util)
target_link_libraries(ngmail smtp)
target_link_libraries(ngmail http)
target_link_libraries(ngmail ${LIBUV_LIBRARY})
target_link_libraries(ngmail ${libpthread_lib})