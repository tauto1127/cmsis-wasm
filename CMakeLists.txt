set(MY_CMAKE_VERSION 3.5.1)
cmake_minimum_required(VERSION ${MY_CMAKE_VERSION})

project(cmsis-posix-project
    VERSION 1.0.0
    DESCRIPTION "cmsis-wasm"
    LANGUAGES C CXX
)

set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON) 

set(CMSIS_INTERFACE_DIR "${PROJECT_SOURCE_DIR}/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2")
set(CMSIS_IMPL_INTERFACE_DIR "${PROJECT_SOURCE_DIR}/src/include")

include(default-cmake-options.cmake)

message(STATUS "BUILD_TYPE " ${BUILD_TYPE})
message(STATUS "GCOV " ${GCOV})

add_subdirectory(src)

set(INSTALL_CMAKE_DIR ${PROJECT_SOURCE_DIR}/public)

install(
	DIRECTORY ${PROJECT_SOURCE_DIR}/src/include/
	DESTINATION ${INSTALL_CMAKE_DIR}/include
)
install(
	DIRECTORY ${CMSIS_INTERFACE_DIR}/
	DESTINATION ${INSTALL_CMAKE_DIR}/include
)

install(
	TARGETS cmsis 
	DESTINATION     ${INSTALL_CMAKE_DIR} 
	EXPORT cmsis-export
    LIBRARY         DESTINATION lib
    INCLUDES        DESTINATION include
    PUBLIC_HEADER   DESTINATION include
)
install(
	EXPORT cmsis-export 
    FILE    cmsis-config.cmake
	DESTINATION ${INSTALL_CMAKE_DIR}
    EXPORT_LINK_INTERFACE_LIBRARIES
)
