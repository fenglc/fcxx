add_library(land SHARED
    algorithm.h
    land.h
    list.h
    pair.h
    test.cpp
    test_creator.h
    test_executor.cpp
    test_executor.h
    test.h
    time_ms.h
)

target_include_directories(land
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../
)

add_library(land-main SHARED
    land_main.cpp
)

target_link_libraries(land-main
    PUBLIC
        land
)

add_library(land::libland ALIAS land)
add_library(land::main ALIAS land-main)
