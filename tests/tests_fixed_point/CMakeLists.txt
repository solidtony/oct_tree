project(tests_fixed_point)

add_executable(${PROJECT_NAME}
    tests_fixed_point.cpp
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        GTest::Main
        fixed_point
)

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
