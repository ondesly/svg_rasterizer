#
# Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 25.07.2020.
#

cmake_minimum_required(VERSION 3.4.1)
project(svg_rasterizer)

#

if(DEFINED ANDROID_ABI)
        set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/../prebuilt/android/${ANDROID_ABI})
endif(DEFINED ANDROID_ABI)

if(DEFINED PLATFORM)
        set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/../prebuilt/ios/${PLATFORM})
endif(DEFINED PLATFORM)

#

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MODULE_PATH 
        ${CMAKE_CURRENT_LIST_DIR}/../deps/cairo/cmake
        ${CMAKE_CURRENT_LIST_DIR}/../deps/numerals/cmake
        ${CMAKE_CURRENT_LIST_DIR}/../deps/pixman/cmake
        ${CMAKE_CURRENT_LIST_DIR}/../deps/pugixml/cmake
        ${CMAKE_CURRENT_LIST_DIR}/../deps/stb/cmake)

find_package(Cairo)
find_package(Numerals)
find_package(Pixman)
find_package(PugiXml)
find_package(Stb)

set(SRC_ROOT ${CMAKE_CURRENT_LIST_DIR}/../src)

include_directories(
        ${CAIRO_INCLUDE_DIRS}
        ${NUMERALS_INCLUDE_DIRS}
        ${PIXMAN_INCLUDE_DIRS}
        ${PUGIXML_INCLUDE_DIRS}
        ${STB_INCLUDE_DIRS}

        ${SRC_ROOT})

set(SRC
        ${SRC_ROOT}/svg/rasterizer.cpp
        ${SRC_ROOT}/svg/renderer.cpp)

add_library(svg STATIC ${SRC} ${CAIRO_SRC} ${PIXMAN_SRC} ${PUGIXML_SRC})