//
// Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 25.07.2020.
//

#include <iostream>

#include <svg/rasterizer.h>

namespace {

    const char *c_svg_sample_1 = R"(<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 10 10"><title>empty</title><rect width="10" height="10" fill="#fff"/></svg>)";

    const char *c_svg_sample_2 = R"(<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 130 130"><path d="M115,117.5a2.49,2.49,0,0,1-1.77-.73l-100-100a2.5,2.5,0,0,1,3.54-3.54l100,100a2.52,2.52,0,0,1,0,3.54A2.49,2.49,0,0,1,115,117.5Z" fill="#fff"/><path d="M15,117.5a2.49,2.49,0,0,1-1.77-.73,2.52,2.52,0,0,1,0-3.54l100-100a2.5,2.5,0,0,1,3.54,3.54l-100,100A2.49,2.49,0,0,1,15,117.5Z" fill="#fff"/></svg>)";

    const char *c_svg_sample_3 = R"(<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 62 62"><circle cx="31" cy="31" r="30" fill="#e6c694"/><circle cx="31" cy="31" r="16" fill="#383631"/><circle cx="31" cy="31" r="14" fill="#e6c694"/></svg>)";

}

int main(int argc, const char * argv[]) {
    svg::rasterizer rasterizer(4096);

    rasterizer.add(c_svg_sample_1, {10, 10}, 2);
    rasterizer.add(c_svg_sample_2, {0, 15}, 2);
    rasterizer.add(c_svg_sample_3, {20, 0}, 2);

    rasterizer.pack();

    const auto size = rasterizer.get_size();
    const auto data = new unsigned int[size.w * size.h];

    std::fill(data, data + size.w * size.h, 0);

    rasterizer.render(data);
    
    std::cout << "Rasterization done!" << std::endl;
    
    return 0;
}
