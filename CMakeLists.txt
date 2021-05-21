#
#  CMakeLists.txt
#  svg_texture_packer
#
#  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 25.07.2020.
#  Copyright © 2020-2021 Dmitrii Torkhov. All rights reserved.
#

cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(svg_texture_packer
        VERSION 1.0.1
        LANGUAGES C CXX)

set(CMAKE_XCODE_ATTRIBUTE_EXCLUDED_ARCHS[sdk=iphonesimulator*] "arm64")

################
# Dependencies #
################

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

#

include(FetchContent)

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
        GIT_REPOSITORY https://github.com/ondesly/stb.git
        GIT_TAG v1.0.0
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE)

FetchContent_Declare(
        vectors
        GIT_REPOSITORY https://github.com/ondesly/vectors.git
        GIT_TAG v1.2.1
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE)

#

FetchContent_MakeAvailable(cairo pixman pugixml stb vectors)

#########
# Build #
#########

add_subdirectory(src)

###########
# Install #
###########

include(GNUInstallDirs)

install(TARGETS ${PROJECT_NAME} cairo pixman pugixml stb
        EXPORT ${PROJECT_NAME}-config
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}${INSTALL_SUFFIX}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}${INSTALL_SUFFIX}/${PROJECT_NAME})

install(EXPORT ${PROJECT_NAME}-config DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})

###########
# Testing #
###########

enable_testing()

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
    add_subdirectory(tests)
endif ()