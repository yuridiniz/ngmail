add_subdirectory(platform)
add_subdirectory(util)

add_executable(ngmail 
    main.c )

target_link_libraries(ngmail platform util)
target_link_libraries(ngmail uv)