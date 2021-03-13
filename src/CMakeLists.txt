#
#  CMakeLists.txt
#  svg_texture_packer
#
#  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 19.10.2020.
#  Copyright © 2020-2021 Dmitrii Torkhov. All rights reserved.
#

find_package(Pixman REQUIRED)
find_package(Cairo REQUIRED)
find_package(Stb REQUIRED)

#

add_library(svg_texture_packer STATIC
        svg/packer.cpp
        svg/renderer.cpp)

target_link_libraries(svg_texture_packer PUBLIC cairo pugixml stb vectors)

#

set(INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/../include)

set(PUBLIC_HEADERS
        ${INCLUDE_DIR}/svg/packer.h
        ${INCLUDE_DIR}/svg/renderer.h)

set_target_properties(svg_texture_packer PROPERTIES PUBLIC_HEADER "${PUBLIC_HEADERS}")

target_include_directories(svg_texture_packer PUBLIC $<BUILD_INTERFACE:${INCLUDE_DIR}> $<INSTALL_INTERFACE:include>)

#

set_target_properties(svg_texture_packer PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED YES CXX_EXTENSIONS NO)