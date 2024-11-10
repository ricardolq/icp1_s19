add_executable(03_common_init 03_common_init.c)

if (WIN32)
    target_link_libraries(03_common_init w2_32)
endif()