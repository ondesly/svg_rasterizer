#
#  CMakeLists.txt
#  svg_texture_packer
#
#  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 08.01.2021.
#  Copyright © 2021 Dmitrii Torkhov. All rights reserved.
#

project(tests)

add_executable(test1 main.cpp)
target_link_libraries(test1 svg)

add_test(NAME Test1 COMMAND test1)