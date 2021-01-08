#
#  FindCairo.cmake
#  svg_texture_packer
#
#  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 25.07.2020.
#  Copyright © 2020-2021 Dmitrii Torkhov. All rights reserved.
#

set(CAIRO_ROOT ${cairo_SOURCE_DIR})

add_definitions(-DHAVE_CONFIG_H)
add_definitions(-DCAIRO_NO_MUTEX)
add_definitions(-DCAIRO_FEATURES_H)

# Config

set(HAVE_STDINT_H 1)
set(HAVE_UINT64_T 1)

FILE(READ ${CAIRO_ROOT}/config.h.in CAIRO_CONFIG)
STRING(REGEX REPLACE "#undef ([A-Z0-9_]+)" "#cmakedefine \\1 @\\1@" CAIRO_CONFIG_MOD ${CAIRO_CONFIG})
FILE(WRITE ${PROJECT_BINARY_DIR}/include/cairo/config.h.in ${CAIRO_CONFIG_MOD})

FILE(WRITE ${PROJECT_BINARY_DIR}/include/cairo/cairo-features.h "")

configure_file(
        ${PROJECT_BINARY_DIR}/include/cairo/config.h.in
        ${PROJECT_BINARY_DIR}/include/cairo/config.h)

#

set(CAIRO_SRC
        ${CAIRO_ROOT}/src/cairo-analysis-surface.c
        ${CAIRO_ROOT}/src/cairo-arc.c
        ${CAIRO_ROOT}/src/cairo-array.c
        ${CAIRO_ROOT}/src/cairo-atomic.c
        ${CAIRO_ROOT}/src/cairo-bentley-ottmann-rectangular.c
        ${CAIRO_ROOT}/src/cairo-bentley-ottmann-rectilinear.c
        ${CAIRO_ROOT}/src/cairo-bentley-ottmann.c
        ${CAIRO_ROOT}/src/cairo-boxes-intersect.c
        ${CAIRO_ROOT}/src/cairo-boxes.c
        ${CAIRO_ROOT}/src/cairo-cache.c
        ${CAIRO_ROOT}/src/cairo-clip-boxes.c
        ${CAIRO_ROOT}/src/cairo-clip-polygon.c
        ${CAIRO_ROOT}/src/cairo-clip-region.c
        ${CAIRO_ROOT}/src/cairo-clip-surface.c
        ${CAIRO_ROOT}/src/cairo-clip.c
        ${CAIRO_ROOT}/src/cairo-color.c
        ${CAIRO_ROOT}/src/cairo-composite-rectangles.c
        ${CAIRO_ROOT}/src/cairo-compositor.c
        ${CAIRO_ROOT}/src/cairo-contour.c
        ${CAIRO_ROOT}/src/cairo-damage.c
        ${CAIRO_ROOT}/src/cairo-debug.c
        ${CAIRO_ROOT}/src/cairo-default-context.c
        ${CAIRO_ROOT}/src/cairo-device.c
        ${CAIRO_ROOT}/src/cairo-error.c
        ${CAIRO_ROOT}/src/cairo-fallback-compositor.c
        ${CAIRO_ROOT}/src/cairo-font-face-twin-data.c
        ${CAIRO_ROOT}/src/cairo-font-face-twin.c
        ${CAIRO_ROOT}/src/cairo-font-face.c
        ${CAIRO_ROOT}/src/cairo-font-options.c
        ${CAIRO_ROOT}/src/cairo-freelist.c
        ${CAIRO_ROOT}/src/cairo-gstate.c
        ${CAIRO_ROOT}/src/cairo-hash.c
        ${CAIRO_ROOT}/src/cairo-hull.c
        ${CAIRO_ROOT}/src/cairo-image-compositor.c
        ${CAIRO_ROOT}/src/cairo-image-source.c
        ${CAIRO_ROOT}/src/cairo-image-surface.c
        ${CAIRO_ROOT}/src/cairo-line.c
        ${CAIRO_ROOT}/src/cairo-mask-compositor.c
        ${CAIRO_ROOT}/src/cairo-matrix.c
        ${CAIRO_ROOT}/src/cairo-mesh-pattern-rasterizer.c
        ${CAIRO_ROOT}/src/cairo-misc.c
        ${CAIRO_ROOT}/src/cairo-mono-scan-converter.c
        ${CAIRO_ROOT}/src/cairo-no-compositor.c
        ${CAIRO_ROOT}/src/cairo-observer.c
        ${CAIRO_ROOT}/src/cairo-output-stream.c
        ${CAIRO_ROOT}/src/cairo-path-bounds.c
        ${CAIRO_ROOT}/src/cairo-path-fill.c
        ${CAIRO_ROOT}/src/cairo-path-fixed.c
        ${CAIRO_ROOT}/src/cairo-path-in-fill.c
        ${CAIRO_ROOT}/src/cairo-path-stroke-boxes.c
        ${CAIRO_ROOT}/src/cairo-path-stroke-polygon.c
        ${CAIRO_ROOT}/src/cairo-path-stroke-traps.c
        ${CAIRO_ROOT}/src/cairo-path-stroke-tristrip.c
        ${CAIRO_ROOT}/src/cairo-path-stroke.c
        ${CAIRO_ROOT}/src/cairo-path.c
        ${CAIRO_ROOT}/src/cairo-pattern.c
        ${CAIRO_ROOT}/src/cairo-pen.c
        ${CAIRO_ROOT}/src/cairo-polygon-intersect.c
        ${CAIRO_ROOT}/src/cairo-polygon-reduce.c
        ${CAIRO_ROOT}/src/cairo-polygon.c
        ${CAIRO_ROOT}/src/cairo-raster-source-pattern.c
        ${CAIRO_ROOT}/src/cairo-recording-surface.c
        ${CAIRO_ROOT}/src/cairo-rectangle.c
        ${CAIRO_ROOT}/src/cairo-rectangular-scan-converter.c
        ${CAIRO_ROOT}/src/cairo-region.c
        ${CAIRO_ROOT}/src/cairo-scaled-font.c
        ${CAIRO_ROOT}/src/cairo-shape-mask-compositor.c
        ${CAIRO_ROOT}/src/cairo-slope.c
        ${CAIRO_ROOT}/src/cairo-spans-compositor.c
        ${CAIRO_ROOT}/src/cairo-spans.c
        ${CAIRO_ROOT}/src/cairo-spline.c
        ${CAIRO_ROOT}/src/cairo-stroke-dash.c
        ${CAIRO_ROOT}/src/cairo-stroke-style.c
        ${CAIRO_ROOT}/src/cairo-surface-offset.c
        ${CAIRO_ROOT}/src/cairo-surface-snapshot.c
        ${CAIRO_ROOT}/src/cairo-surface-wrapper.c
        ${CAIRO_ROOT}/src/cairo-surface.c
        ${CAIRO_ROOT}/src/cairo-tor-scan-converter.c
        ${CAIRO_ROOT}/src/cairo-tor22-scan-converter.c
        ${CAIRO_ROOT}/src/cairo-toy-font-face.c
        ${CAIRO_ROOT}/src/cairo-traps-compositor.c
        ${CAIRO_ROOT}/src/cairo-traps.c
        ${CAIRO_ROOT}/src/cairo-tristrip.c
        ${CAIRO_ROOT}/src/cairo-unicode.c
        ${CAIRO_ROOT}/src/cairo-user-font.c
        ${CAIRO_ROOT}/src/cairo-wideint.c
        ${CAIRO_ROOT}/src/cairo.c)

set_source_files_properties(${CAIRO_SRC} PROPERTIES COMPILE_FLAGS "-w")

#

add_library(cairo STATIC ${CAIRO_SRC})

target_link_libraries(cairo PRIVATE pixman)

target_include_directories(cairo PUBLIC
        $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include/cairo>
        $<BUILD_INTERFACE:${CAIRO_ROOT}/src>)