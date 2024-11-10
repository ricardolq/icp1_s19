add_executable(04_time_server 04_time_server.c)

if (WIN32)
    target_link_libraries(00_init_win w2_32)
endif()