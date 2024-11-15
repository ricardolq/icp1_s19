add_executable(09_tcp_server_select 09_tcp_server_select.c)

if (WIN32)
    target_link_libraries(09_tcp_server_select w2_32)
endif()