cmake_minimum_required(VERSION 2.8)
project(Nominal CXX)

set(NOM_MAJOR_VERSION 0)
set(NOM_MINOR_VERSION 0)
set(NOM_PATCH_VERSION 1)
set(NOM_VERSION ${NOM_MAJOR_VERSION}.${NOM_MINOR_VERSION}.${NOM_PATCH_VERSION})

set(OUTPUT_DIR "${CMAKE_BINARY_DIR}/Output" CACHE PATH "Output directory for built files")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})

foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${OUTPUT_DIR})
endforeach()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include_directories(
    SYSTEM "${PROJECT_SOURCE_DIR}/Dependencies/Catch"
    )

add_subdirectory("${PROJECT_SOURCE_DIR}/Executable")
add_subdirectory("${PROJECT_SOURCE_DIR}/Library")
add_subdirectory("${PROJECT_SOURCE_DIR}/Tests")
