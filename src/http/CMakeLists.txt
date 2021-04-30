set(http_src 
    http.c 
)

add_library(http STATIC ${http_src})

target_link_libraries(http platform util)
