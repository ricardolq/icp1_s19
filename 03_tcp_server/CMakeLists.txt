add_executable(03_tcp_server 03_tcp_server.c)

if (WIN32)
    target_link_libraries(02_time_server w2_32)
endif()