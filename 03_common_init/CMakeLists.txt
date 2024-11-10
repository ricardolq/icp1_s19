add_executable(03_common_init 03_common_init.c)

if (WIN32)
    target_link_libraries(00_init_win w2_32)
endif()