//
//  test_pack.cpp
//  svg_texture_packer
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 08.01.2021.
//  Copyright © 2021 Dmitrii Torkhov. All rights reserved.
//

#include <sstream>

#include <svg_texture_packer/packer.h>

namespace {

    const char *c_svg_sample_rect = R"(<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 10 10"><title>empty</title><rect width="10" height="10" fill="#fff"/></svg>)";

    const char *c_svg_sample_doll = R"(<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 200 333.33"><title>kokeshi</title><path d="M88.89,138.89a5.56,5.56,0,0,0,11.11,0v-5.56H88.89Z" fill="#383631"/><path d="M188.89,222.22h0a11.12,11.12,0,0,0-11.11-11.11h0A11.11,11.11,0,0,0,166.67,200h0a11.11,11.11,0,0,0-11.11-11.11h0a11.11,11.11,0,0,0-11.12-11.11h0a11.1,11.1,0,0,0-11.11-11.11h0a11.11,11.11,0,0,1,11.11-11.11h0a11.12,11.12,0,0,0,11.12-11.12h0a11.11,11.11,0,0,0,11.11-11.11h0V55.56h0a11.12,11.12,0,0,0-11.11-11.12V33.33h0a11.12,11.12,0,0,0-11.12-11.11h0a11.11,11.11,0,0,0-11.11-11.11h0A11.1,11.1,0,0,0,122.22,0H66.67A11.1,11.1,0,0,0,55.56,11.11h0A11.12,11.12,0,0,0,44.44,22.22h0A11.12,11.12,0,0,0,33.33,33.33h0V44.44h0A11.12,11.12,0,0,0,22.22,55.56h0v77.77h0a11.11,11.11,0,0,0,11.11,11.11h0a11.12,11.12,0,0,0,11.11,11.12,11.11,11.11,0,0,1,11.12,11.11v11.11h0a11.11,11.11,0,0,0-11.12,11.11h0A11.11,11.11,0,0,0,33.33,200h0a11.11,11.11,0,0,0-11.11,11.11h0a11.12,11.12,0,0,0-11.11,11.11h0A11.11,11.11,0,0,0,0,233.33H0v11.11H0a11.11,11.11,0,0,0,11.11,11.12,11.12,11.12,0,0,0,11.11,11.11h0a11.12,11.12,0,0,0,11.11,11.11h0a11.1,11.1,0,0,1,11.11,11.11c6.14,0,9.63,3.7,11.12,9.63,1.48-5.93,5-9.63,11.11-9.63a11.1,11.1,0,0,1,11.11-11.11,11.1,11.1,0,0,1,11.11-11.11,11.12,11.12,0,0,1-11.11,11.11,11.12,11.12,0,0,1-11.11,11.11,11.12,11.12,0,0,1-22.23,0,11.12,11.12,0,0,1-11.11-11.11v33.33h0a11.11,11.11,0,0,0,11.11,11.11,11.11,11.11,0,0,0,11.12,11.11h77.77a11.1,11.1,0,0,0,11.11-11.11h0a11.11,11.11,0,0,0,11.12-11.11h0V277.78a11.12,11.12,0,0,1-22.23,0,11.12,11.12,0,0,1-11.11-11.11,11.1,11.1,0,0,1,11.11,11.11c6.14,0,9.63,3.7,11.11,9.63,1.49-5.93,5-9.63,11.12-9.63a11.12,11.12,0,0,0,11.11-11.11h0a11.12,11.12,0,0,0,11.11-11.11h0a11.12,11.12,0,0,0,11.11-11.12h0A11.1,11.1,0,0,0,200,233.33h0A11.11,11.11,0,0,0,188.89,222.22Zm-66.67,44.45a11.12,11.12,0,0,1-11.11-11.11A11.1,11.1,0,0,1,122.22,266.67Zm-5.55,34.07c3.06,0,5.55,2.16,5.55,4.82s-2.49,4.81-5.55,4.81-5.56-2.16-5.56-4.81S113.6,300.74,116.67,300.74ZM100,305.56c0,2.65-2.49,4.81-5.56,4.81s-5.55-2.16-5.55-4.81,2.49-4.82,5.55-4.82S100,302.9,100,305.56Zm.74-11.12c0-3.06,2.16-5.55,4.82-5.55s4.81,2.49,4.81,5.55-2.16,5.56-4.81,5.56S100.74,297.51,100.74,294.44ZM100,255.56a11.11,11.11,0,0,1-11.11-11.12V233.33a11.11,11.11,0,0,1,22.22,0v11.11A11.11,11.11,0,0,1,100,255.56ZM55.56,188.89A11.11,11.11,0,0,1,66.67,200a11.11,11.11,0,0,1,11.11,11.11,11.12,11.12,0,0,1,11.11,11.11,11.1,11.1,0,0,1-11.11-11.11A11.1,11.1,0,0,1,66.67,200a11.1,11.1,0,0,1-11.11-11.11Zm122.22,38.89c0,2.66-2.49,4.81-5.56,4.81s-5.55-2.15-5.55-4.81,2.48-4.82,5.55-4.82S177.78,225.12,177.78,227.78Zm-11.85-11.11c0,3.06-2.16,5.55-4.82,5.55s-4.81-2.49-4.81-5.55,2.15-5.56,4.81-5.56S165.93,213.6,165.93,216.67Zm-77,5.55h0V211.11h0ZM54.81,261.11c0,3.07-2.15,5.56-4.81,5.56s-4.81-2.49-4.81-5.56,2.15-5.55,4.81-5.55S54.81,258,54.81,261.11Zm0-22.22c0,3.07-2.15,5.55-4.81,5.55s-4.81-2.48-4.81-5.55,2.15-5.56,4.81-5.56S54.81,235.82,54.81,238.89Zm-15.92,6.3c3.07,0,5.55,2.15,5.55,4.81s-2.48,4.81-5.55,4.81-5.56-2.15-5.56-4.81S35.82,245.19,38.89,245.19Zm22.22,9.62c-3.07,0-5.55-2.15-5.55-4.81s2.48-4.81,5.55-4.81,5.56,2.15,5.56,4.81S64.18,254.81,61.11,254.81ZM100,183.33c0-2.66,2.49-4.81,5.56-4.81s5.55,2.15,5.55,4.81-2.49,4.82-5.55,4.82S100,186,100,183.33Zm-.74,11.11c0,3.07-2.16,5.56-4.82,5.56s-4.81-2.49-4.81-5.56,2.16-5.55,4.81-5.55S99.26,191.38,99.26,194.44ZM83.33,178.52c3.07,0,5.56,2.15,5.56,4.81s-2.49,4.82-5.56,4.82-5.55-2.16-5.55-4.82S80.27,178.52,83.33,178.52Zm38.89,32.59a11.1,11.1,0,0,1-11.11,11.11A11.12,11.12,0,0,1,122.22,211.11ZM150,232.59c-3.07,0-5.56-2.15-5.56-4.81S146.93,223,150,223s5.56,2.16,5.56,4.82S153.07,232.59,150,232.59Zm-27.78-10.37h0V211.11h0Zm-23-50c0,3.07-2.16,5.56-4.82,5.56s-4.81-2.49-4.81-5.56,2.16-5.55,4.81-5.55S99.26,169.15,99.26,172.22Zm57,66.67c0-3.07,2.15-5.56,4.81-5.56s4.82,2.49,4.82,5.56-2.16,5.55-4.82,5.55S156.3,242,156.3,238.89Zm-23-38.89a11.1,11.1,0,0,1-11.11,11.11A11.11,11.11,0,0,1,133.33,200a11.11,11.11,0,0,1,11.11-11.11A11.1,11.1,0,0,1,133.33,200Zm-11.11-44.44H66.67a11.11,11.11,0,0,1-11.11-11.12,11.11,11.11,0,0,1-11.12-11.11V111.11A11.11,11.11,0,0,1,55.56,100h77.77a11.1,11.1,0,0,1,11.11,11.11v22.22a11.1,11.1,0,0,1-11.11,11.11,11.11,11.11,0,0,1-11.11,11.12h0ZM116.67,56.3c3.06,0,5.55,2.15,5.55,4.81s-2.49,4.82-5.55,4.82-5.56-2.16-5.56-4.82S113.6,56.3,116.67,56.3ZM123,72.22c0-3.07,2.16-5.55,4.82-5.55s4.81,2.48,4.81,5.55-2.15,5.56-4.81,5.56S123,75.29,123,72.22Zm15.93-6.29c-3.07,0-5.56-2.16-5.56-4.82s2.49-4.81,5.56-4.81,5.55,2.15,5.55,4.81S142,65.93,138.89,65.93ZM132.59,50c0,3.07-2.15,5.56-4.81,5.56S123,53.07,123,50s2.16-5.56,4.82-5.56S132.59,46.93,132.59,50Zm-77-16.67V31.14a11.11,11.11,0,0,1,8.91-8.92h2.2A11.11,11.11,0,0,1,77.78,11.11H88.89A11.11,11.11,0,0,1,77.78,22.22H66.67v2.2a11.11,11.11,0,0,1-8.92,8.91H55.56V44.44A11.12,11.12,0,0,1,44.44,55.56V44.44A11.12,11.12,0,0,1,55.56,33.33ZM33.33,211.11A11.11,11.11,0,0,1,44.44,200a11.1,11.1,0,0,1-11.11,11.11,11.1,11.1,0,0,1-11.11,11.11A11.12,11.12,0,0,1,33.33,211.11Zm67.41,105.56c0-3.07,2.16-5.56,4.82-5.56s4.81,2.49,4.81,5.56-2.16,5.55-4.81,5.55S100.74,319.73,100.74,316.67Zm21.48-50V255.56h0v11.11Z" fill="#383631"/><path d="M66.67,111.11c-6.14,0-11.11,4.22-11.11,9.43s22.22,5.21,22.22,0S72.8,111.11,66.67,111.11Z" fill="#383631"/><path d="M133.33,120.54c0-5.21-5-9.43-11.11-9.43s-11.11,4.22-11.11,9.43S133.33,125.75,133.33,120.54Z" fill="#383631"/></svg>)";

    const char *right_result = "000023543515649600000255255255255255255255255000023543515649600000255255255255255255255255000023543515649600000255255255255255255255255000035424054565647600002552552552552552552552550006434056565648562500002552552552552552552552550003651545656494141550000255255255255255255255255000375656565656415656000025525525525525525525525500037565656565656565600002552552552552552552552550003743870212265600000000000000037371414062319560000000000000001848902101383400000000000000001443373737432410000000000000000242523749563520000000000000000354552374956453500000000000022230465642545442564835222000000003535355156565434345449414135353500000000555555564141562020565641563535350000000019191955414156504451565636222000000000001851564651564649330000000000000000454051564156471800000000000000005456564141495618000000000000000019555656485636200000000000000001955565648563620000000000000000195556564856362000000000000";

    const size_t c_max_texture_size = 4096;

}

int main(const int argc, const char *argv[]) {
    svg::packer packer(c_max_texture_size);

    //

    packer.add(c_svg_sample_rect, {4, 4}, 2);
    packer.add(c_svg_sample_doll, {0, 20}, 2);

    packer.pack();

    //

    const auto size = packer.get_size();
    const auto data = new unsigned int[size.width * size.height];

    std::fill(data, data + size.width * size.height, 0);

    packer.render(data);

    //

    const std::vector<unsigned char> v_data(data, data + size.width * size.height);
    std::stringstream result;
    for (const auto c : v_data) {
        result << int(c);
    }

    return result.str() == right_result ? 0 : 1;
}