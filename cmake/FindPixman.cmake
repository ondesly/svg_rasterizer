#
#  FindPixman.cmake
#  svg_texture_packer
#
#  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 25.07.2020.
#  Copyright © 2020-2021 Dmitrii Torkhov. All rights reserved.
#

set(PIXMAN_ROOT ${pixman_SOURCE_DIR})

add_definitions(-DHAVE_CONFIG_H)
add_definitions(-DPIXMAN_NO_TLS)

# Config

set(PACKAGE pixman)

FILE(READ ${PIXMAN_ROOT}/config.h.in PIXMAN_CONFIG)
STRING(REGEX REPLACE "#undef ([A-Z0-9_]+)" "#cmakedefine \\1 @\\1@" PIXMAN_CONFIG_MOD ${PIXMAN_CONFIG})
FILE(WRITE ${PROJECT_BINARY_DIR}/include/pixman/config.h.in "${PIXMAN_CONFIG_MOD}")

configure_file (
    ${PROJECT_BINARY_DIR}/include/pixman/config.h.in
    ${PROJECT_BINARY_DIR}/include/pixman/config.h
)

#

set(PIXMAN_SRC
    ${PIXMAN_ROOT}/pixman/pixman.h
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
    ${PIXMAN_ROOT}/pixman/pixman-utils.c
)

set_source_files_properties(${PIXMAN_SRC} PROPERTIES COMPILE_FLAGS "-w")

#

add_library(pixman STATIC ${PIXMAN_SRC})

target_include_directories(pixman PUBLIC 
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include/pixman>
    $<BUILD_INTERFACE:${PIXMAN_ROOT}/pixman>
)