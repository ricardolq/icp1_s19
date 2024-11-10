add_executable(00_init_win 00_init_win.c)

if (WIN32)
    target_link_libraries(00_init_win w2_32)
endif()
