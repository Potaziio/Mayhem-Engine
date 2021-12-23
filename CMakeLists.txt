cmake_minimum_required(VERSION 3.0.0)
project(Mayhem VERSION 0.0.1)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

if(POLICY CMP0072)
    cmake_policy(SET CMP0072 NEW)
endif()

find_package(OpenGL REQUIRED)

file (GLOB SOURCE_FILES
    "Mayhem/src/*/*.cpp"
    "Mayhem/src/*/*/*.cpp"
    "Mayhem/src/*/*/*/*.cpp"
    "Mayhem/src/*.cpp"
    )

file (GLOB IMGUI_SOURCES
    "include/vendor/imgui-docking/*.cpp"
    )

file(GLOB GLEW_SOURCES
    "include/vendor/glew-2.2.0/src/*"
    )

file (GLOB INCLUDE_DIRS 
    "include/vendor/glew-2.2.0/include/GL/*.h"
    "include/vendor/stb_image/stb_image.h"
    "include/vendor/imgui-docking/*.h"
    "include/vendor/glm/*.hpp"
    )

add_subdirectory("include/vendor/glfw-3.3.5/" glfw)

add_library(glew_lib STATIC ${GLEW_SOURCES})
add_library(imgui_lib STATIC ${IMGUI_SOURCES})

add_executable(Mayhem ${SOURCE_FILES})

target_link_libraries(Mayhem PUBLIC imgui_lib glew_lib glfw OpenGL::GL ${CMAKE_DL_LIBS})
