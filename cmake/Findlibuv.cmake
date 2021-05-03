
set(LIBUV_STATIC_LIB ON)

# Configura a biblioteca para link statico
if(${LIBUV_STATIC_LIB}) 
    if(UNIX)
        set(CMAKE_C_FLAGS "-Wno-dev -Wl,--no-as-needed -ldl")
    endif()

    list(INSERT CMAKE_FIND_LIBRARY_SUFFIXES 0 ${CMAKE_STATIC_LIBRARY_SUFFIX})
endif()

FIND_PATH(LIBUV_INCLUDE_DIRS
    NAMES uv.h
    HINTS "${CMAKE_SOURCE_DIR}/third_part/libuv/include/"
)
FIND_LIBRARY(LIBUV_LIBRARY 
    NAMES uv_a uv libuv
    HINTS 
    "${CMAKE_SOURCE_DIR}/third_part/libuv/build/Debug/"
    "${CMAKE_SOURCE_DIR}/third_part/libuv/build/Release/"
    "${CMAKE_SOURCE_DIR}/third_part/libuv/build/"
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(libuv DEFAULT_MSG LIBUV_LIBRARY LIBUV_INCLUDE_DIRS)

# Remove as configurações específicas do link
if(${LIBUV_STATIC_LIB}) 
    list(REMOVE_AT CMAKE_FIND_LIBRARY_SUFFIXES 0)
endif()
