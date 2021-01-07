#
#  CMakeLists.txt
#  svg_rasterizer
#
#  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 19.10.2020.
#  Copyright © 2020-2021 Dmitrii Torkhov. All rights reserved.
#

set_source_files_properties(${PUGIXML_SRC} PROPERTIES COMPILE_FLAGS "-w")

#

set(SRC
    svg/rasterizer.cpp
    svg/renderer.cpp)

add_library(svg STATIC
    ${PUGIXML_SRC}

    ${SRC})

target_link_libraries(svg PRIVATE cairo)

set_target_properties(svg PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO)

target_include_directories(svg PRIVATE
    ${NUMERALS_INCLUDE_DIRS}
    ${PUGIXML_INCLUDE_DIRS}
    ${STB_INCLUDE_DIRS}

    ../include)

#

set(PUBLIC_HEADERS 
    ../include/svg/rasterizer.h
    ../include/svg/renderer.h)

install(TARGETS svg cairo pixman
        EXPORT svg-config
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include)

install(FILES ${PUBLIC_HEADERS} DESTINATION include/svg)

install(EXPORT svg-config DESTINATION lib/cmake/svg)