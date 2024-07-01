project(fixed_point)

add_library(${PROJECT_NAME} STATIC
    inc/FixedPoint32.h
    src/FixedPoint32.cpp
    inc/FixedPoint64.h
    src/FixedPoint64.cpp
    inc/FixedPointTypeDefs.h
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<INSTALL_INTERFACE:inc>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/inc
)
