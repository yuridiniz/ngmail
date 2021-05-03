include_directories("${CMAKE_SOURCE_DIR}/src/")

find_package(libuv REQUIRED)
IF (LIBUV_FOUND)
    message(${LIBUV_INCLUDE_DIRS})
    include_directories("${LIBUV_INCLUDE_DIRS}")
    # LINK_DIRECTORIES(${LIBUV_LIBRARY_DIRS})
ENDIF (LIBUV_FOUND)

if(UNIX)
    # Refatorar isso no FIND
    # Try to find the header
    FIND_PATH(libpthread_dir NAMES pthread.h)
    # Try to find the library
    FIND_LIBRARY(libpthread_lib NAMES pthread)
endif()

add_subdirectory(platform)
add_subdirectory(util)
add_subdirectory(smtp)
add_subdirectory(http)

set(main_src 
    main.c 
    server.c
)

add_executable(ngmail ${main_src})

target_link_libraries(ngmail platform)
target_link_libraries(ngmail util)
target_link_libraries(ngmail smtp)
target_link_libraries(ngmail http)
target_link_libraries(ngmail ${LIBUV_LIBRARY})

if(UNIX)
    target_link_libraries(ngmail ${libpthread_lib})
endif()

if(WIN32)
    # Insere bibliotecas necessárias para implementação de socket no windows
    # Necessita para geração estática do libuv
    target_link_libraries(ngmail wsock32 ws2_32 iphlpapi userenv psapi secur32)
endif()