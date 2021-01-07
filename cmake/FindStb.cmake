#
#  FindStb.cmake
#  svg_rasterizer
#
#  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 25.07.2020.
#  Copyright © 2020-2021 Dmitrii Torkhov. All rights reserved.
#

add_library(stb INTERFACE)

target_include_directories(stb INTERFACE
    $<BUILD_INTERFACE:${stb_SOURCE_DIR}>
)