add_executable(01_common_init 01_common_init.c)

if (WIN32)
    target_link_libraries(01_common_init w2_32)
endif()