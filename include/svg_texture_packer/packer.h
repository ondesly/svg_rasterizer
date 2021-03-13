//
//  packer.h
//  svg_texture_packer
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 23.07.2020.
//  Copyright © 2020-2021 Dmitrii Torkhov. All rights reserved.
//

#pragma once

#include <string>
#include <vector>

#include <vectors/vec2.h>
#include <vectors/vec4.h>

struct stbrp_context;
struct stbrp_node;
struct stbrp_rect;

namespace pugi {

    class xml_document;

}

namespace svg {

    using size_t2 = oo::vec2<size_t>;
    using size_t4 = oo::vec4<size_t>;
    using float4 = oo::vec4<float>;

    struct item;

    class packer {
    public:

        packer(size_t max_texture_size);

        ~packer();

    public:

        void add(const std::string &content, const size_t2 &size, size_t padding);

        void pack();

        void render(unsigned short *data);

        void render(unsigned int *data);

        void make_size_pow_of_2();

        const size_t2 &get_size() const;

        const size_t4 &get_rect(size_t index) const;

    private:

        stbrp_context *m_context = nullptr;
        stbrp_rect *m_rects = nullptr;
        stbrp_node *m_nodes = nullptr;

        std::vector<item> m_items;

        size_t2 m_size = {0, 0};

    private:

        pugi::xml_document *parse_content(const std::string &content);

        float4 parse_view_box(const char *s);

    };

}
