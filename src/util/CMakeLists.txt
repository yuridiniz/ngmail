set(util_src 
    string.c 
    # shared_ptr.c
)

add_library(util STATIC ${util_src})