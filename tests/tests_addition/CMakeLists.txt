project(tests_addition)

add_executable(${PROJECT_NAME}
    tests_addition.cpp
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        GTest::Main
        addition
)

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
