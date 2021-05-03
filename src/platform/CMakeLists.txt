set(PLAT "${CMAKE_SOURCE_DIR}/src/platform/${platform_host}")

message("Linking... ${PLAT}")

set(platform_src  
    ${PLAT}/load_module.c
    ${PLAT}/thread.c
)

add_library(platform STATIC ${platform_src})