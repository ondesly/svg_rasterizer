//
//  ViewController.mm
//  svg_rasterizer
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 30.09.2020.
//  Copyright © 2020 Dmitrii Torkhov. All rights reserved.
//

#include <svg/rasterizer.h>

#import "ViewController.h"

@interface ViewController ()

@end

@implementation ViewController

namespace {
    
    std::string to_string(NSString *string) {
        return [string cStringUsingEncoding:NSUTF8StringEncoding];
    }
    
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    NSString *path = [[NSBundle mainBundle] pathForResource:@"res/doll" ofType:@"svg"];
    NSString *content = [NSString stringWithContentsOfFile:path encoding:NSUTF8StringEncoding error:nil];
    
    //
    
    svg::rasterizer packer(4096);
    packer.add(to_string(content), {0, 128}, 0);
    
    packer.pack();
    
    const auto size = packer.get_size();
    auto data = new unsigned char[size.w * size.h * 4];
    std::fill(data, data + size.w * size.h * 4, '\0');
    
    packer.render(reinterpret_cast<unsigned int *>(data));
    
    //
    
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
    CGContextRef bitmapContext = CGBitmapContextCreate(data, size.w, size.h, 8, size.w * 4, colorSpace,  kCGImageAlphaPremultipliedLast | kCGBitmapByteOrderDefault);
    CGImageRef cgImage = CGBitmapContextCreateImage(bitmapContext);

    UIImage *newimage = [UIImage imageWithCGImage:cgImage];
    [_ImageView setImage:newimage];
    
    CGImageRelease(cgImage);
    CGContextRelease(bitmapContext);
    CFRelease(colorSpace);
    delete[] data;
}


@end
