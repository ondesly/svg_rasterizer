//
//  renderer.cpp
//  svg_texture_packer
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 23.07.2020.
//  Copyright © 2020-2021 Dmitrii Torkhov. All rights reserved.
//

#include <sstream>
#include <unordered_map>
#include <vector>

#include <cairo.h>
#include <vectors/vec2.h>
#include <pugixml.hpp>

#include "svg_texture_packer/renderer.h"

namespace {

    namespace bpc {

        const size_t rgb565 = 2;
        const size_t rgba8888 = 4;

    }

}

void svg::renderer::render(unsigned short *data, const svg::size_t2 &size, const item &item) {
    auto data8 = reinterpret_cast<unsigned char *>(data);
    auto surface = cairo_image_surface_create_for_data(data8, CAIRO_FORMAT_RGB16_565, int(size.width), int(size.height), int(size.width * bpc::rgb565));
    auto cr = cairo_create(surface);

    //

    render(cr, item.document->child("svg"), item.rect, item.scale, {0, 1, 2, 3});

    //

    cairo_destroy(cr);
    cairo_surface_destroy(surface);

    //

    extrude(data8, size, bpc::rgb565, item.rect, item.padding);
}

void svg::renderer::render(unsigned int *data, const svg::size_t2 &size, const item &item) {
    auto data8 = reinterpret_cast<unsigned char *>(data);
    auto surface = cairo_image_surface_create_for_data(data8, CAIRO_FORMAT_ARGB32, int(size.width), int(size.height), int(size.width * bpc::rgba8888));
    auto cr = cairo_create(surface);

    //

    render(cr, item.document->child("svg"), item.rect, item.scale, {2, 1, 0, 3});

    //

    cairo_destroy(cr);
    cairo_surface_destroy(surface);

    //

    extrude(data8, size, bpc::rgba8888, item.rect, item.padding);
}

void svg::renderer::render(cairo_t *cr, const pugi::xml_node &root, const svg::size_t4 &rect, float scale, const svg::size_t4 &ci) {
    cairo_save(cr);

    cairo_move_to(cr, rect.x, rect.y);
    cairo_rel_line_to(cr, rect.width, 0.);
    cairo_rel_line_to(cr, 0., rect.height);
    cairo_rel_line_to(cr, -rect.width, 0.);
    cairo_clip(cr);

    cairo_translate(cr, rect.x, rect.y);
    cairo_scale(cr, scale, scale);

    // Iterate

    for (auto &node : root.children()) {
        if (strcmp(node.attribute("fill").as_string(), "none") == 0) {
            continue;
        }

        // Draw

        if (std::strcmp(node.name(), "path") == 0) {
            render_path(cr, node);
        } else if (std::strcmp(node.name(), "polygon") == 0) {
            render_polygon(cr, node);
        } else if (std::strcmp(node.name(), "rect") == 0) {
            render_rect(cr, node);
        } else if (std::strcmp(node.name(), "circle") == 0) {
            render_circle(cr, node);
        } else if (std::strcmp(node.name(), "ellipse") == 0) {
            render_ellipse(cr, node);
        } else {
            continue;
        }

        // Set color

        const auto color = parse_color(node.attribute("fill").as_string(nullptr), node.attribute("opacity").as_string(nullptr));
        cairo_set_source_rgba(cr, color[ci[0]], color[ci[1]], color[ci[2]], color[ci[3]]);

        // Fill

        cairo_fill(cr);
    }

    //

    cairo_restore(cr);
}

void svg::renderer::extrude(unsigned char *data, const svg::size_t2 &size, size_t bpc, const svg::size_t4 &rect, size_t padding) {

    // V

    for (auto i = rect.y - 1; i <= rect.y + rect.height + 1; ++i) {
        for (auto j = 0; j < padding; ++j) {
            std::copy_n(
                    data + (rect.x + i * size.width) * bpc,
                    bpc,
                    data + (rect.x - 1 - j + i * size.width) * bpc
            );

            std::copy_n(
                    data + (rect.x + rect.width - 1 + i * size.width) * bpc,
                    bpc,
                    data + (rect.x + rect.width + j + i * size.width) * bpc
            );
        }
    }

    // H

    for (auto i = 0; i < padding; ++i) {
        std::copy_n(
                data + (rect.x - padding + rect.y * size.width) * bpc,
                (rect.width + padding * 2) * bpc,
                data + (rect.x - padding + (rect.y - 1 - i) * size.width) * bpc
        );

        std::copy_n(
                data + (rect.x - padding + (rect.y + rect.height - 1) * size.width) * bpc,
                (rect.width + padding * 2) * bpc,
                data + (rect.x - padding + (rect.y + rect.height + i) * size.width) * bpc
        );
    }
}

namespace {

    double hex1_to_double(const char *array, size_t start) {
        char value[2] = {array[start]};
        return std::strtol(value, nullptr, 16) / 15.;
    }

    double hex2_to_double(const char *array, size_t start) {
        char value[3] = {array[start], array[start + 1]};
        return std::strtol(value, nullptr, 16) / 255.;
    }

    constexpr unsigned int hash(const char *s, int off = 0) {
        return !s[off] ? 5381 : (hash(s, off + 1) * 33) ^ s[off];
    }

    const std::unordered_map<unsigned int, const char *> keywords = {
            {hash("lime"), "#00ff00"}, {hash("silver"), "#c0c0c0"}, {hash("gray"), "#808080"},
            {hash("white"), "#ffffff"}, {hash("maroon"), "#800000"}, {hash("red"), "#ff0000"},
            {hash("purple"), "#800080"}, {hash("fuchsia"), "#ff00ff"}, {hash("green"), "#008000"},
            {hash("lime"), "#00ff00"}, {hash("olive"), "#808000"}, {hash("yellow"), "#ffff00"},
            {hash("navy"), "#000080"}, {hash("blue"), "#0000ff"}, {hash("teal"), "#008080"},
            {hash("aqua"), "#00ffff"}, {hash("orange"), "#ffa500"}, {hash("plum"), "#dda0dd"}
    };

}

svg::renderer::double4 svg::renderer::parse_color(const char *fill, const char *opacity) {
    if (fill) {
        if (fill[0] != '#') {
            auto it = keywords.find(hash(fill));
            fill = it != keywords.end() ? it->second : fill;
        }

        if (strlen(fill) == 4) {
            return {
                    hex1_to_double(fill, 1),
                    hex1_to_double(fill, 2),
                    hex1_to_double(fill, 3),
                    opacity ? std::atof(opacity) : 1.
            };
        } else if (strlen(fill) == 7) {
            return {
                    hex2_to_double(fill, 1),
                    hex2_to_double(fill, 3),
                    hex2_to_double(fill, 5),
                    opacity ? std::atof(opacity) : 1.
            };
        }
    }

    return {1., 1., 1., 1.};
}

namespace {

    namespace command {

        const char absolute_move = 'M';
        const char relative_move = 'm';
        const char absolute_line = 'L';
        const char relative_line = 'l';
        const char absolute_horizontal = 'H';
        const char relative_horizontal = 'h';
        const char absolute_vertical = 'V';
        const char relative_vertical = 'v';
        const char absolute_curve = 'C';
        const char relative_curve = 'c';
        const char absolute_smooth_curve = 'S';
        const char relative_smooth_curve = 's';
        const char absolute_quadratic_curve = 'Q';
        const char relative_quadratic_curve = 'q';
        const char absolute_together_curve = 'T';
        const char relative_together_curve = 't';
        const char absolute_arc = 'A';
        const char relative_arc = 'a';
        const char absolute_close = 'Z';
        const char relative_close = 'z';

    };

}

void svg::renderer::render_path(cairo_t *cr, const pugi::xml_node &node) {
    auto src = node.attribute("d").as_string();

    params params;
    char cmd = 0;
    char prev_cmd = 0;

    while (*src != 0) {
        if (*src - 'A' >= 0) {
            cmd = *src;
            ++src;
        }

        parse_parameters(cr, cmd, prev_cmd, params, src);

        switch (cmd) {
            case command::absolute_move:
                cairo_move_to(cr, params.x, params.y);
                break;
            case command::relative_move:
                cairo_rel_move_to(cr, params.x, params.y);
                break;
            case command::absolute_line:
                cairo_line_to(cr, params.x, params.y);
                break;
            case command::relative_line:
                cairo_rel_line_to(cr, params.x, params.y);
                break;
            case command::absolute_horizontal:
                cairo_line_to(cr, params.x, params.y0);
                break;
            case command::relative_horizontal:
                cairo_rel_line_to(cr, params.x, 0.);
                break;
            case command::absolute_vertical:
                cairo_line_to(cr, params.x0, params.y);
                break;
            case command::relative_vertical:
                cairo_rel_line_to(cr, 0., params.y);
                break;
            case command::absolute_curve:
                cairo_curve_to(cr, params.x1, params.y1, params.x2, params.y2, params.x3, params.y3);
                break;
            case command::relative_curve:
                cairo_rel_curve_to(cr, params.x1, params.y1, params.x2, params.y2, params.x3, params.y3);
                break;
            case command::absolute_smooth_curve:
                cairo_curve_to(cr, params.x1, params.y1, params.x2, params.y2, params.x3, params.y3);
                break;
            case command::relative_smooth_curve:
                cairo_rel_curve_to(cr, params.x1, params.y1, params.x2, params.y2, params.x3, params.y3);
                break;
            case command::absolute_quadratic_curve:
            case command::absolute_together_curve:
                cairo_curve_to(cr,
                        2. / 3. * params.x1 + 1. / 3. * params.x0, 2. / 3. * params.y1 + 1. / 3. * params.y0,
                        2. / 3. * params.x1 + 1. / 3. * params.x3, 2. / 3. * params.y1 + 1. / 3. * params.y3,
                        params.x3, params.y3);
                break;
            case command::relative_quadratic_curve:
            case command::relative_together_curve:
                cairo_rel_curve_to(cr,
                        2. / 3. * params.x1, 2. / 3. * params.y1,
                        2. / 3. * params.x1 + 1. / 3. * params.x3, 2. / 3. * params.y1 + 1. / 3. * params.y3,
                        params.x3, params.y3);
                break;
            case command::absolute_arc:
            case command::relative_arc:
                arc(cr, params.rx, params.ry, params.rotation, params.large_arc_flag, params.sweep_flag,
                        params.x, params.y, params.x0, params.y0);
                break;
            case command::absolute_close:
            case command::relative_close:
                cairo_close_path(cr);
                break;
            default:
                break;
        }

        prev_cmd = cmd;
    }
}

void svg::renderer::parse_parameters(cairo_t *cr, char cmd, char prev_cmd, svg::renderer::params &params, const char *&src) {
    cairo_get_current_point(cr, &params.x0, &params.y0);

    switch (cmd) {
        case command::absolute_move:
        case command::relative_move:
        case command::absolute_line:
        case command::relative_line:
            parse(src, &params.x, &params.y);
            break;
        case command::absolute_horizontal:
        case command::relative_horizontal:
            parse(src, &params.x, &params.x);
            break;
        case command::absolute_vertical:
        case command::relative_vertical:
            parse(src, &params.y, &params.y);
            break;
        case command::absolute_curve:
        case command::relative_curve:
            parse(src, &params.x1, &params.y3);
            break;
        case command::absolute_smooth_curve:
            parse_parameters_by_previous(prev_cmd, params, params.x0, params.y0);
            parse(src, &params.x2, &params.y3);
            break;
        case command::relative_smooth_curve:
            parse_parameters_by_previous(prev_cmd, params, 0., 0.);
            parse(src, &params.x2, &params.y3);
            break;
        case command::absolute_quadratic_curve:
        case command::relative_quadratic_curve:
            parse(src, &params.x1, &params.y1);
            parse(src, &params.x3, &params.y3);
            break;
        case command::absolute_together_curve:
            parse_parameters_by_previous(prev_cmd, params, params.x0, params.y0);
            parse(src, &params.x3, &params.y3);
            break;
        case command::relative_together_curve:
            parse_parameters_by_previous(prev_cmd, params, 0., 0.);
            parse(src, &params.x3, &params.y3);
            break;
        case command::absolute_arc:
            parse(src, &params.rx, &params.rotation);
            parse(src, &params.large_arc_flag, &params.sweep_flag);
            parse(src, &params.x, &params.y);

            params.x -= params.x0;
            params.y -= params.y0;
            break;
        case command::relative_arc:
            parse(src, &params.rx, &params.rotation);
            parse(src, &params.large_arc_flag, &params.sweep_flag);
            parse(src, &params.x, &params.y);
            break;
        default:
            break;
    }
}

void svg::renderer::parse_parameters_by_previous(char prev_cmd, svg::renderer::params &params, double x0, double y0) {
    switch (prev_cmd) {
        case command::absolute_curve:
        case command::absolute_smooth_curve:
            params.x1 = -(params.x2 - params.x0) + x0;
            params.y1 = -(params.y2 - params.y0) + y0;
            break;
        case command::relative_curve:
        case command::relative_smooth_curve:
            params.x1 = -(params.x2 - params.x3) + x0;
            params.y1 = -(params.y2 - params.y3) + y0;
            break;
        case command::absolute_quadratic_curve:
        case command::absolute_together_curve:
            params.x1 = -(params.x1 - params.x0) + x0;
            params.y1 = -(params.y1 - params.y0) + y0;
            break;
        case command::relative_quadratic_curve:
        case command::relative_together_curve:
            params.x1 = -(params.x1 - params.x3) + x0;
            params.y1 = -(params.y1 - params.y3) + y0;
            break;
        default:
            params.x1 = x0;
            params.y1 = y0;
            break;
    }
}

void svg::renderer::parse(const char *&src, double *dst, double *dst2) {
    char *end;
    while (dst <= dst2) {
        *dst = std::strtod(src, &end);
        ++dst;

        src = *end == ',' ? end + 1 : end;
    }
}

void svg::renderer::parse(const char *&src, long *dst, long *dst2) {
    char *end;
    while (dst <= dst2) {
        *dst = std::strtol(src, &end, 10);
        ++dst;

        src = *end == ',' ? end + 1 : end;
    }
}

void svg::renderer::render_polygon(cairo_t *cr, const pugi::xml_node &node) {
    const auto src = node.attribute("points").as_string();

    std::vector<float> points;

    //

    std::stringstream stream(src);

    float point;
    while (stream >> point) {
        points.push_back(point);
    }

    //

    cairo_move_to(cr, points[0], points[1]);

    for (size_t i = 2; i < points.size(); i += 2) {
        cairo_line_to(cr, points[i], points[i + 1]);
    }

    cairo_close_path(cr);
}

void svg::renderer::render_rect(cairo_t *cr, const pugi::xml_node &node) {
    const float x = node.attribute("x").as_float();
    const float y = node.attribute("y").as_float();
    const float w = node.attribute("width").as_float();
    const float h = node.attribute("height").as_float();

    cairo_move_to(cr, x, y);

    cairo_rel_line_to(cr, w, 0.);
    cairo_rel_line_to(cr, 0., h);
    cairo_rel_line_to(cr, -w, 0.);

    cairo_close_path(cr);
}

void svg::renderer::render_circle(cairo_t *cr, const pugi::xml_node &node) {
    const auto cx = node.attribute("cx").as_float();
    const auto cy = node.attribute("cy").as_float();
    const auto r = node.attribute("r").as_float();

    cairo_move_to(cr, cx - r, cy);

    double x0, y0;

    cairo_get_current_point(cr, &x0, &y0);
    arc(cr, r, r, 0., 1, 0, r + r, 0., x0, y0);

    cairo_get_current_point(cr, &x0, &y0);
    arc(cr, r, r, 0., 1, 0, -(r + r), 0., x0, y0);

    cairo_close_path(cr);
}

void svg::renderer::render_ellipse(cairo_t *cr, const pugi::xml_node &node) {
    const auto cx = node.attribute("cx").as_float();
    const auto cy = node.attribute("cy").as_float();
    const auto rx = node.attribute("rx").as_float();
    const auto ry = node.attribute("ry").as_float();

    cairo_move_to(cr, cx - rx, cy);

    double x0, y0;

    cairo_get_current_point(cr, &x0, &y0);
    arc(cr, rx, ry, 0., 1, 0, rx + ry, 0., x0, y0);

    cairo_get_current_point(cr, &x0, &y0);
    arc(cr, rx, ry, 0., 1, 0, -(rx + ry), 0., x0, y0);

    cairo_close_path(cr);
}

void svg::renderer::arc(cairo_t *cr, double rx, double ry, double rotation, long large_arc_flag, long sweep_flag, double x, double y, double x0, double y0) {
    if (rx <= 0 || ry / rx <= 0) {
        return;
    }

    transform(-rotation * 0.017453292519943, x, y, x, y);

    y /= ry / rx;
    auto angle = std::atan2(y, x);
    x = std::sqrt(x * x + y * y);

    auto xc = x / 2;
    auto rxc = std::max(rx, xc);
    auto yc = std::sqrt(rxc * rxc - xc * xc) * (large_arc_flag ^ sweep_flag ? 1 : -1);

    transform(angle, xc, yc, xc, yc);
    transform(angle, x, 0., x, y);

    //

    cairo_save(cr);

    cairo_translate(cr, x0, y0);
    cairo_rotate(cr, rotation * 0.017453292519943);
    cairo_scale(cr, 1, ry / rx);

    if (sweep_flag) {
        cairo_arc(cr, xc, yc, rxc, std::atan2(-yc, -xc), std::atan2(y - yc, x - xc));
    } else {
        cairo_arc_negative(cr, xc, yc, rxc, std::atan2(-yc, -xc), std::atan2(y - yc, x - xc));
    }

    cairo_restore(cr);
}

void svg::renderer::transform(double angle, double x, double y, double &dst_x, double &dst_y) {
    dst_x = x * std::cos(angle) - y * std::sin(angle);
    dst_y = y * std::cos(angle) + x * std::sin(angle);
}
