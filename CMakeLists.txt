cmake_minimum_required(VERSION 3.23)
project(tracking)

set(CMAKE_CXX_STANDARD 20)

#include directory for openvr
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/openvr/include")

#link directory for openvr
link_directories("${CMAKE_CURRENT_SOURCE_DIR}/openvr/lib")

#add src files to build
file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)

#add library target and add files from src
add_library(tracking SHARED  ${SOURCES})

set(CMAKE_SHARED_LINKER_FLAGS "-static-libgcc -static-libstdc++")

#links openvr
target_link_libraries(tracking openvr_api)


#copies openvr_api.dll to the binary folder
add_custom_command(
        TARGET tracking PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/openvr/lib/openvr_api.dll
                ${CMAKE_BINARY_DIR}/openvr_api.dll)