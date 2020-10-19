#
#  CMakeLists.txt
#  svg_rasterizer
#
#  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 25.07.2020.
#  Copyright © 2020 Dmitrii Torkhov. All rights reserved.
#

cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(svg_rasterizer 
    VERSION 0.1
    LANGUAGES C CXX)

################
# Dependencies #
################

include(FetchContent)

set(FETCHCONTENT_QUIET FALSE)
set(FETCHCONTENT_BASE_DIR ${CMAKE_CURRENT_LIST_DIR}/deps)

#

FetchContent_Declare(
    cairo
    GIT_REPOSITORY  git://anongit.freedesktop.org/git/cairo
    GIT_TAG         1.12.10
    GIT_SHALLOW     TRUE
    GIT_PROGRESS    TRUE)

FetchContent_Declare(
    pixman
    GIT_REPOSITORY  git://anongit.freedesktop.org/git/pixman.git
    GIT_TAG         pixman-0.32.4
    GIT_SHALLOW     TRUE
    GIT_PROGRESS    TRUE)

FetchContent_Declare(
    numerals
    GIT_REPOSITORY  https://github.com/ondesly/numerals.git
    GIT_TAG         ac3d2ef6a0584d8b75c2fa2b9810486a32d4c616
    GIT_SHALLOW     TRUE
    GIT_PROGRESS    TRUE)

FetchContent_Declare(
    pugixml
    GIT_REPOSITORY  https://github.com/zeux/pugixml.git
    GIT_TAG         v1.10
    GIT_SHALLOW     TRUE
    GIT_PROGRESS    TRUE)

FetchContent_Declare(
    stb
    GIT_REPOSITORY  https://github.com/nothings/stb.git
    GIT_TAG         b42009b3b9d4ca35bc703f5310eedc74f584be58
    GIT_SHALLOW     TRUE
    GIT_PROGRESS    TRUE)

#

FetchContent_MakeAvailable(cairo pixman numerals pugixml stb)

#########
# Build #
#########

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

find_package(Cairo)
find_package(Numerals)
find_package(Pixman)
find_package(PugiXml)
find_package(Stb)

#

set(SRC_ROOT ${CMAKE_CURRENT_LIST_DIR}/src)

set(SRC
    ${SRC_ROOT}/svg/rasterizer.cpp
    ${SRC_ROOT}/svg/renderer.cpp)

add_library(svg STATIC 
    ${CAIRO_SRC}
    ${PIXMAN_SRC}
    ${PUGIXML_SRC}

    ${SRC})

set_target_properties(svg PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO)

target_include_directories(svg PRIVATE
    ${CAIRO_INCLUDE_DIRS}
    ${NUMERALS_INCLUDE_DIRS}
    ${PIXMAN_INCLUDE_DIRS}
    ${PUGIXML_INCLUDE_DIRS}
    ${STB_INCLUDE_DIRS}

    ${SRC_ROOT}
    ${SRC_ROOT}/cairo
    ${SRC_ROOT}/pixman)