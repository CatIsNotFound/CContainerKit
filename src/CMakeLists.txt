cmake_minimum_required(VERSION 3.10)

include(GNUInstallDirs)

file(GLOB_RECURSE LIB_SOURCES CONFIGURE_DEPENDS *.c)

add_library(${PROJECT_NAME} STATIC ${LIB_SOURCES}
        ../include/CContainerKit/CVariant.h
        ../include/CContainerKit/CArray.h
        CVariant.c
        CArray.c
        ../include/CContainerKit/CVector.h
        CVector.c
        ../include/CContainerKit/CDebug.h
        CDebug.c
        ../include/CContainerKit.h
        ../include/CContainerKit/CString.h
        CString.c
        ../include/CContainerKit/CStack.h
        CStack.c
        ../include/CContainerKit/CDeque.h
        CDeque.c
        ../include/CContainerKit/CNode.h
        CNode.c
        ../include/CContainerKit/CLinkedList.h
        CLinkedList.c
        ../include/CContainerKit/CMap.h
        ../include/CContainerKit/CPair.h
        CPair.c
        CMap.c
        ../include/CContainerKit/CAlgorithm.h
        ../include/CContainerKit/CTree.h
        CTree.c
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
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
    DIRECTORY ${CMAKE_SOURCE_DIR}/include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)