add_executable(01_listing_win 01_listing_win.c)
if (WIN32)
    target_link_libraries(01_listing_win w2_32 iphlpapi)
endif()