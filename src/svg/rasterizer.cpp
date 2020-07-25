//
// Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 23.07.2020.
//

#define STB_RECT_PACK_IMPLEMENTATION

#include <pugixml/pugixml.hpp>
#include <stb/stb_rect_pack.h>

#include "svg/renderer.h"

#include "rasterizer.h"

namespace {

    constexpr size_t pow_of_2(size_t x) {
        --x;
        x |= x >> 1;
        x |= x >> 2;
        x |= x >> 4;
        x |= x >> 8;
        x |= x >> 16;
        return x + 1;
    }

}

svg::rasterizer::rasterizer(size_t max_texture_size) {
    m_context = new stbrp_context;
    m_nodes = new stbrp_node[max_texture_size];

    stbrp_init_target(m_context, int(max_texture_size), int(max_texture_size), m_nodes, int(max_texture_size));
}

svg::rasterizer::~rasterizer() {
    for (auto item : m_items) {
        delete item.document;
    }

    delete[] m_rects;
    delete[] m_nodes;
    delete m_context;
}

void svg::rasterizer::render(unsigned short *data) {
    renderer renderer;

    for (const auto &item : m_items) {
        renderer.render(data, m_size, item);
    }
}

void svg::rasterizer::render(unsigned int *data) {
    renderer renderer;

    for (const auto &item : m_items) {
        renderer.render(data, m_size, item);
    }
}

void svg::rasterizer::pack() {
    m_rects = new stbrp_rect[m_items.size()];

    auto rect = m_rects;
    for (const auto &item : m_items) {
        rect->w = stbrp_coord(item.rect.w + item.padding * 2);
        rect->h = stbrp_coord(item.rect.h + item.padding * 2);

        ++rect;
    }

    if (!stbrp_pack_rects(m_context, m_rects, int(m_items.size()))) {
        return;
    }

    rect = m_rects;
    for (auto &item : m_items) {
        item.rect.x = rect->x + item.padding;
        item.rect.y = rect->y + item.padding;

        m_size.w = std::max(m_size.w, size_t(rect->x + rect->w));
        m_size.h = std::max(m_size.h, size_t(rect->y + rect->h));

        ++rect;
    }
}

void svg::rasterizer::make_size_pow_of_2() {
    m_size.w = pow_of_2(m_size.w);
    m_size.h = pow_of_2(m_size.h);
}

const cc::size_t2 &svg::rasterizer::get_size() const {
    return m_size;
}

const cc::size_t4 &svg::rasterizer::get_rect(size_t index) const {
    return m_items[index].rect;
}

void svg::rasterizer::add(const std::string &content, const cc::size_t2 &size, size_t padding) {
    auto document = parse_content(content);

    if (!document) {
        return;
    }

    item item{document, {0, 0, size.w, size.h}, padding, 1.F};

    // Size

    const auto root = document->child("svg");
    const auto view_box = parse_view_box(root.attribute("viewBox").as_string());

    if (item.rect.w == 0) {
        item.rect.w = size_t(view_box.w * item.rect.h / view_box.h);
    } else if (item.rect.h == 0) {
        item.rect.h = size_t(view_box.h * item.rect.w / view_box.w);
    }

    // Scale

    item.scale = std::max(item.rect.w / view_box.w, item.rect.h / view_box.h);

    //

    m_items.push_back(item);
}

pugi::xml_document *svg::rasterizer::parse_content(const std::string &content) {
    auto document = new pugi::xml_document;
    const auto result = document->load_string(content.c_str());

    if (result.status == pugi::xml_parse_status::status_ok) {
        return document;
    } else {
        delete document;
        return nullptr;
    }
}

cc::float4 svg::rasterizer::parse_view_box(const char *s) {
    cc::float4 box;
    std::sscanf(s, "%f %f %f %f", &box.x, &box.y, &box.w, &box.h);
    return box;
}
