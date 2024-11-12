add_executable(02_time_server 02_time_server.c)

if (WIN32)
    target_link_libraries(02_time_server w2_32)
endif()