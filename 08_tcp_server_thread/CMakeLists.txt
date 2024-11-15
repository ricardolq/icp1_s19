add_executable(08_tcp_server_thread 08_tcp_server_thread.c)

if (WIN32)
    target_link_libraries(08_tcp_server_thread w2_32)
endif()