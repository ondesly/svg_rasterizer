set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DPIXMAN_NO_TLS")

set(PIXMAN_ROOT ${CMAKE_CURRENT_LIST_DIR}/..)

set(PIXMAN_INCLUDE_DIRS ${PIXMAN_ROOT}/include ${PIXMAN_ROOT}/src/pixman)

set(PIXMAN_SRC
    ${PIXMAN_ROOT}/src/pixman/pixman.c
    ${PIXMAN_ROOT}/src/pixman/pixman-access-accessors.c
    ${PIXMAN_ROOT}/src/pixman/pixman-access.c
    ${PIXMAN_ROOT}/src/pixman/pixman-bits-image.c
    ${PIXMAN_ROOT}/src/pixman/pixman-combine-float.c
    ${PIXMAN_ROOT}/src/pixman/pixman-combine32.c
    ${PIXMAN_ROOT}/src/pixman/pixman-conical-gradient.c
    ${PIXMAN_ROOT}/src/pixman/pixman-filter.c
    ${PIXMAN_ROOT}/src/pixman/pixman-x86.c
    ${PIXMAN_ROOT}/src/pixman/pixman-mips.c
    ${PIXMAN_ROOT}/src/pixman/pixman-arm.c
    ${PIXMAN_ROOT}/src/pixman/pixman-ppc.c
    ${PIXMAN_ROOT}/src/pixman/pixman-edge-accessors.c
    ${PIXMAN_ROOT}/src/pixman/pixman-edge.c
    ${PIXMAN_ROOT}/src/pixman/pixman-fast-path.c
    ${PIXMAN_ROOT}/src/pixman/pixman-general.c
    ${PIXMAN_ROOT}/src/pixman/pixman-glyph.c
    ${PIXMAN_ROOT}/src/pixman/pixman-gradient-walker.c
    ${PIXMAN_ROOT}/src/pixman/pixman-image.c
    ${PIXMAN_ROOT}/src/pixman/pixman-implementation.c
    ${PIXMAN_ROOT}/src/pixman/pixman-linear-gradient.c
    ${PIXMAN_ROOT}/src/pixman/pixman-matrix.c
    ${PIXMAN_ROOT}/src/pixman/pixman-noop.c
    ${PIXMAN_ROOT}/src/pixman/pixman-radial-gradient.c
    ${PIXMAN_ROOT}/src/pixman/pixman-region16.c
    ${PIXMAN_ROOT}/src/pixman/pixman-region32.c
    ${PIXMAN_ROOT}/src/pixman/pixman-solid-fill.c
    ${PIXMAN_ROOT}/src/pixman/pixman-timer.c
    ${PIXMAN_ROOT}/src/pixman/pixman-trap.c
    ${PIXMAN_ROOT}/src/pixman/pixman-utils.c)