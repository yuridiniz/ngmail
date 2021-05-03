set(smtp_src 
    smtp.c 
    command_handler.c 
    data_handler.c 
)

add_library(smtp STATIC ${smtp_src})

target_link_libraries(smtp platform util)
