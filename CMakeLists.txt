cmake_minimum_required(VERSION 3.0.0)
project(ngmail VERSION 0.1.0)

SET(CMAKE_MODULE_PATH APPEND "${CMAKE_SOURCE_DIR}/cmake")

if (WIN32)
    message("SO: WIN32")
    set(platform_host "win")
elseif(UNIX)
    message("SO: UNIX")
    set(platform_host "unix")
endif()


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

add_subdirectory(src)