#
#  FindPixman.cmake
#  svg_rasterizer
#
#  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 25.07.2020.
#  Copyright © 2020 Dmitrii Torkhov. All rights reserved.
#

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DPACKAGE=\"pixman\" -DPIXMAN_NO_TLS=1 -DPIXMAN_VERSION=0 -DPIXMAN_VERSION_STRING=\"0\"")

set(PIXMAN_ROOT ${pixman_SOURCE_DIR})

set(PIXMAN_INCLUDE_DIRS ${PIXMAN_ROOT}/pixman)

set(PIXMAN_SRC
    ${PIXMAN_ROOT}/pixman/pixman.c
    ${PIXMAN_ROOT}/pixman/pixman-access-accessors.c
    ${PIXMAN_ROOT}/pixman/pixman-access.c
    ${PIXMAN_ROOT}/pixman/pixman-bits-image.c
    ${PIXMAN_ROOT}/pixman/pixman-combine-float.c
    ${PIXMAN_ROOT}/pixman/pixman-combine32.c
    ${PIXMAN_ROOT}/pixman/pixman-conical-gradient.c
    ${PIXMAN_ROOT}/pixman/pixman-filter.c
    ${PIXMAN_ROOT}/pixman/pixman-x86.c
    ${PIXMAN_ROOT}/pixman/pixman-mips.c
    ${PIXMAN_ROOT}/pixman/pixman-arm.c
    ${PIXMAN_ROOT}/pixman/pixman-ppc.c
    ${PIXMAN_ROOT}/pixman/pixman-edge-accessors.c
    ${PIXMAN_ROOT}/pixman/pixman-edge.c
    ${PIXMAN_ROOT}/pixman/pixman-fast-path.c
    ${PIXMAN_ROOT}/pixman/pixman-general.c
    ${PIXMAN_ROOT}/pixman/pixman-glyph.c
    ${PIXMAN_ROOT}/pixman/pixman-gradient-walker.c
    ${PIXMAN_ROOT}/pixman/pixman-image.c
    ${PIXMAN_ROOT}/pixman/pixman-implementation.c
    ${PIXMAN_ROOT}/pixman/pixman-linear-gradient.c
    ${PIXMAN_ROOT}/pixman/pixman-matrix.c
    ${PIXMAN_ROOT}/pixman/pixman-noop.c
    ${PIXMAN_ROOT}/pixman/pixman-radial-gradient.c
    ${PIXMAN_ROOT}/pixman/pixman-region16.c
    ${PIXMAN_ROOT}/pixman/pixman-region32.c
    ${PIXMAN_ROOT}/pixman/pixman-solid-fill.c
    ${PIXMAN_ROOT}/pixman/pixman-trap.c
    ${PIXMAN_ROOT}/pixman/pixman-utils.c)