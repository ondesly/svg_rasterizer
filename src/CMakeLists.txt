#
#  CMakeLists.txt
#  svg_rasterizer
#
#  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 19.10.2020.
#  Copyright © 2020 Dmitrii Torkhov. All rights reserved.
#

set_source_files_properties(${CAIRO_SRC} PROPERTIES COMPILE_FLAGS "-w")
set_source_files_properties(${PIXMAN_SRC} PROPERTIES COMPILE_FLAGS "-w")
set_source_files_properties(${PUGIXML_SRC} PROPERTIES COMPILE_FLAGS "-w")

#

set(SRC
    svg/rasterizer.cpp
    svg/renderer.cpp)

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

    ../include
    cairo
    pixman)