add_executable(03_tcp_server 03_tcp_server.c)

if (WIN32)
    target_link_libraries(03_tcp_server ws2_32)
endif()