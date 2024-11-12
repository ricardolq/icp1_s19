add_executable(05_udp_server 05_udp_server.c)

if (WIN32)
    target_link_libraries(05_udp_server w2_32)
endif()