#
#  CMakeLists.txt
#  svg_texture_packer
#
#  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 19.10.2020.
#  Copyright © 2020-2021 Dmitrii Torkhov. All rights reserved.
#

add_library(svg STATIC
    svg/packer.cpp
    svg/renderer.cpp
)

target_link_libraries(svg PRIVATE cairo pugixml stb numerals)

set_target_properties(svg PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO)

target_include_directories(svg PRIVATE ../include)

#

set(PUBLIC_HEADERS
    ../include/svg/packer.h
    ../include/svg/renderer.h)

install(TARGETS svg cairo pixman stb
        EXPORT svg-config
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include)

install(FILES ${PUBLIC_HEADERS} DESTINATION include/svg)

install(EXPORT svg-config DESTINATION lib/cmake/svg)