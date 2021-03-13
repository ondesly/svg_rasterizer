//
//  renderer.h
//  svg_texture_packer
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 23.07.2020.
//  Copyright © 2020-2021 Dmitrii Torkhov. All rights reserved.
//

#pragma once

#include <vectors/vec4.h>

struct _cairo;
typedef struct _cairo cairo_t;

struct _cairo_surface;
typedef struct _cairo_surface cairo_surface_t;

namespace oo {

    template<class T, class S>
    struct vec2;

}

namespace pugi {

    class xml_node;

}

namespace svg {

    using size_t2 = oo::vec2<size_t, size_t>;
    using size_t4 = oo::vec4<size_t>;

    struct item {

        pugi::xml_document *document;
        size_t4 rect;
        size_t padding;
        float scale;

    };

    class renderer {
    public:

        void render(unsigned short *data, const size_t2 &size, const item &item);

        void render(unsigned int *data, const size_t2 &size, const item &item);

    private:


    private:

        struct params {
            double x0;
            double y0;
            double x1;
            double y1;
            double x2;
            double y2;
            double x3;
            double y3;

            double rx;
            double ry;
            double rotation;
            long large_arc_flag;
            long sweep_flag;

            double x;
            double y;
        };

    private:

        using double4 = oo::vec4<double>;

    private:

        void render(cairo_t *cr, const pugi::xml_node &root, const size_t4 &rect, float scale, const size_t4 &ci);

        void extrude(unsigned char *data, const size_t2 &size, size_t bpc, const size_t4 &rect, size_t padding);

        double4 parse_color(const char *fill, const char *opacity);

        void render_path(cairo_t *cr, const pugi::xml_node &node);

        void parse_parameters(cairo_t *cr, char cmd, char prev_cmd, params &params, const char *&src);

        void parse_parameters_by_previous(char prev_cmd, params &params, double x0, double y0);

        void parse(const char *&src, double *dst, double *dst2);

        void parse(const char *&src, long *dst, long *dst2);

        void render_polygon(cairo_t *cr, const pugi::xml_node &node);

        void render_rect(cairo_t *cr, const pugi::xml_node &node);

        void render_circle(cairo_t *cr, const pugi::xml_node &node);

        void render_ellipse(cairo_t *cr, const pugi::xml_node &node);

        void arc(cairo_t *cr, double rx, double ry, double rotation, long large_arc_flag, long sweep_flag,
                 double x, double y, double x0, double y0);

        void transform(double angle, double x, double y, double &dst_x, double &dst_y);

    };

}