//
//  packer.cpp
//  svg_texture_packer
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 23.07.2020.
//  Copyright © 2020-2021 Dmitrii Torkhov. All rights reserved.
//

#define STB_RECT_PACK_IMPLEMENTATION

#include <pugixml.hpp>
#include <stb_rect_pack.h>

#include "svg_texture_packer/renderer.h"

#include "svg_texture_packer/packer.h"

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

svg::packer::packer(size_t max_texture_size) {
    m_context = new stbrp_context;
    m_nodes = new stbrp_node[max_texture_size];

    stbrp_init_target(m_context, int(max_texture_size), int(max_texture_size), m_nodes, int(max_texture_size));
}

svg::packer::~packer() {
    for (auto item : m_items) {
        delete item.document;
    }

    delete[] m_rects;
    delete[] m_nodes;
    delete m_context;
}

void svg::packer::render(unsigned short *data) {
    renderer renderer;

    for (const auto &item : m_items) {
        renderer.render(data, m_size, item);
    }
}

void svg::packer::render(unsigned int *data) {
    renderer renderer;

    for (const auto &item : m_items) {
        renderer.render(data, m_size, item);
    }
}

void svg::packer::pack() {
    m_rects = new stbrp_rect[m_items.size()];

    auto rect = m_rects;
    for (const auto &item : m_items) {
        rect->w = stbrp_coord(item.rect.width + item.padding * 2);
        rect->h = stbrp_coord(item.rect.height + item.padding * 2);

        ++rect;
    }

    if (!stbrp_pack_rects(m_context, m_rects, int(m_items.size()))) {
        return;
    }

    rect = m_rects;
    for (auto &item : m_items) {
        item.rect.x = rect->x + item.padding;
        item.rect.y = rect->y + item.padding;

        m_size.width = std::max(m_size.width, size_t(rect->x + rect->w));
        m_size.height = std::max(m_size.height, size_t(rect->y + rect->h));

        ++rect;
    }
}

void svg::packer::make_size_pow_of_2() {
    m_size.width = pow_of_2(m_size.width);
    m_size.height = pow_of_2(m_size.height);
}

const svg::size_t2 &svg::packer::get_size() const {
    return m_size;
}

const svg::size_t4 &svg::packer::get_rect(size_t index) const {
    return m_items[index].rect;
}

void svg::packer::add(const std::string &content, const svg::size_t2 &size, size_t padding) {
    auto document = parse_content(content);

    if (!document) {
        return;
    }

    item item{document, {0, 0, size.width, size.height}, padding, 1.F};

    // Size

    const auto root = document->child("svg");
    const auto view_box = parse_view_box(root.attribute("viewBox").as_string());

    if (item.rect.width == 0) {
        item.rect.width = size_t(view_box.width * item.rect.height / view_box.height);
    } else if (item.rect.height == 0) {
        item.rect.height = size_t(view_box.height * item.rect.width / view_box.width);
    }

    // Scale

    item.scale = std::max(item.rect.width / view_box.width, item.rect.height / view_box.height);

    //

    m_items.push_back(item);
}

pugi::xml_document *svg::packer::parse_content(const std::string &content) {
    auto document = new pugi::xml_document;
    const auto result = document->load_string(content.c_str());

    if (result.status == pugi::xml_parse_status::status_ok) {
        return document;
    } else {
        delete document;
        return nullptr;
    }
}

svg::float4 svg::packer::parse_view_box(const char *s) {
    float4 box;
    std::sscanf(s, "%f %f %f %f", &box.x, &box.y, &box.width, &box.height);
    return box;
}
