#
#  CMakeLists.txt
#  svg_texture_packer
#
#  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 25.07.2020.
#  Copyright © 2020-2021 Dmitrii Torkhov. All rights reserved.
#

cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(svg_texture_packer
        VERSION 0.1
        LANGUAGES C CXX)

set(CMAKE_XCODE_ATTRIBUTE_EXCLUDED_ARCHS[sdk=iphonesimulator*] "arm64")

################
# Dependencies #
################

include(FetchContent)

set(FETCHCONTENT_QUIET FALSE)
set(FETCHCONTENT_BASE_DIR ${CMAKE_CURRENT_LIST_DIR}/extern)

#

FetchContent_Declare(
        cairo
        URL https://www.cairographics.org/releases/cairo-1.16.0.tar.xz)

FetchContent_Declare(
        pixman
        URL https://www.cairographics.org/releases/pixman-0.40.0.tar.gz)

FetchContent_Declare(
        pugixml
        GIT_REPOSITORY https://github.com/zeux/pugixml.git
        GIT_TAG v1.10
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE)

FetchContent_Declare(
        stb
        GIT_REPOSITORY https://github.com/nothings/stb.git
        GIT_TAG b42009b3b9d4ca35bc703f5310eedc74f584be58
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE)

FetchContent_Declare(
        numerals
        GIT_REPOSITORY https://github.com/ondesly/numerals.git
        GIT_TAG 1.0
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE)

#

FetchContent_MakeAvailable(cairo pixman pugixml stb numerals)

#########
# Build #
#########

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

find_package(Pixman REQUIRED)
find_package(Cairo REQUIRED)
find_package(Stb REQUIRED)

#

add_subdirectory(src)

###########
# Testing #
###########

enable_testing()

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
    add_subdirectory(tests)
endif()