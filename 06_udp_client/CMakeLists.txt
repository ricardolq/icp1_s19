add_executable(06_udp_client 06_udp_client.c)

if (WIN32)
    target_link_libraries(06_udp_client PRIVATE ws2_32)
endif()