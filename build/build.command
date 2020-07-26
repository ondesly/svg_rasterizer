#!/bin/sh
#
# Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 25.07.2020.
#

cd "$(dirname "$0")"

rm -rf prebuilt

# iOS Devices

rm -rf build
mkdir build
cd build

cmake .. -DCMAKE_TOOLCHAIN_FILE=../toolchain/ios.toolchain.cmake -DPLATFORM="OS"
make

# iOS Simulator

cd ..
rm -rf build
mkdir build
cd build

cmake .. -DCMAKE_TOOLCHAIN_FILE=../toolchain/ios.toolchain.cmake -DPLATFORM="SIMULATOR64"
make

cd ..
rm -rf build

# iOS Fat

cd ..

lipo -create prebuilt/ios/OS/libsvg.a prebuilt/ios/SIMULATOR64/libsvg.a -output prebuilt/ios/libsvg.a
rm -rf prebuilt/ios/OS
rm -rf prebuilt/ios/SIMULATOR64