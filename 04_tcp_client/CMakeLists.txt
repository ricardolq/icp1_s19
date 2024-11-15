add_executable(04_tcp_client 04_tcp_client.c)

if (WIN32)
    target_link_libraries(04_tcp_client w2_32)
endif()