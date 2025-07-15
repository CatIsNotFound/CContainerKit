cmake_minimum_required(VERSION 3.10)

project(TEST_CContainerKit C)

add_executable(${PROJECT_NAME} 
    main.c
        unit_tests/Test_CArray.h
        unit_tests/Test_CVector.h
        unit_tests/Test_CString.h
        unit_tests/Test_CDebug.h
)
target_link_libraries(${PROJECT_NAME} PRIVATE CContainerKit)
