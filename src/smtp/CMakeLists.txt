set(smtp_src 
    smtp.c 
)

add_library(smtp STATIC ${smtp_src})

target_link_libraries(smtp platform util)
