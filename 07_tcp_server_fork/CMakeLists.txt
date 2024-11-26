add_executable(07_tcp_server_fork 07_tcp_server_fork.c)

if (WIN32)
    target_link_libraries(07_tcp_server_fork ws2_32)
endif()