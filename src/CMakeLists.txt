cmake_minimum_required(VERSION 3.10)

file(GLOB_RECURSE LIB_SOURCES CONFIGURE_DEPENDS *.c)

# LOCAL FILES
set(INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/src)
set(CContainerKit_INCLUDE_DIRS "${INCLUDE_DIRS}")
set(CContainerKit_LIB_DIR      "${PROJECT_SOURCE_DIR}/lib")
set(CContainerKit_CMAKE_DIR    "${PROJECT_BINARY_DIR}/cmake")


add_library(${PROJECT_NAME} STATIC ${LIB_SOURCES}
        ../include/CContainerKit/CVariant.h
        ../include/CContainerKit/CArray.h
        CVariant.c
        ../include/CContainerKit/CString.h
        CString.c
        CArray.c
        ../include/CContainerKit/CVector.h
        CVector.c
        ../include/CContainerKit/CDebug.h
        CDebug.c
        ../include/CContainerKit/CContainerKit.h
)

target_include_directories(${PROJECT_NAME}
        PUBLIC
        $<BUILD_INTERFACE:${INCLUDE_DIRS}>
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

install(
    TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}Targets
    ARCHIVE DESTINATION ${CContainerKit_LIB_DIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
    FILES ${CMAKE_BINARY_DIR}/src/@PROJECT_NAME@Config.cmake
    DESTINATION ${CContainerKit_CMAKE_DIR}
)