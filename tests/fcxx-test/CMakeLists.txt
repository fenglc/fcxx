add_executable(fcxx-test
    cassert_test.cpp
)

target_include_directories(fcxx-test
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(fcxx-test
    land::main
)

add_test(NAME fcxx-test COMMAND fcxx-test)
