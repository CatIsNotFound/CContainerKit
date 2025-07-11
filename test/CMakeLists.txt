cmake_minimum_required(VERSION 3.10)

project(TEST_CContainerKit C)

add_executable(${PROJECT_NAME} 
    main.c
        unit_tests/carray_test.h
        unit_tests/cvector_test.h
)
target_link_libraries(${PROJECT_NAME} PRIVATE CContainerKit)
