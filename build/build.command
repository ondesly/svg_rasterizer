#!/bin/sh
#
# Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 25.07.2020.
#

if [ -z "$NDK_HOME" ]
then
      echo "NDK_HOME is empty"
      exit
fi

#

cd "$(dirname "$0")"

rm -rf ../prebuilt

# iOS Devices

rm -rf build
mkdir build
cd build

cmake .. -DCMAKE_TOOLCHAIN_FILE=../toolchain/ios.toolchain.cmake -DPLATFORM="OS" -DDEPLOYMENT_TARGET="11.0" -DENABLE_BITCODE=FALSE -DENABLE_ARC=FALSE -DENABLE_VISIBILITY=FALSE -DENABLE_STRICT_TRY_COMPILE=FALSE
make

# iOS Simulator

cd ..
rm -rf build
mkdir build
cd build

cmake .. -DCMAKE_TOOLCHAIN_FILE=../toolchain/ios.toolchain.cmake -DPLATFORM="SIMULATOR64" -DDEPLOYMENT_TARGET="11.0" -DENABLE_BITCODE=FALSE -DENABLE_ARC=FALSE -DENABLE_VISIBILITY=FALSE -DENABLE_STRICT_TRY_COMPILE=FALSE
make

# iOS Fat

cd ..
cd ..

lipo -create prebuilt/ios/OS/libsvg.a prebuilt/ios/SIMULATOR64/libsvg.a -output prebuilt/ios/libsvg.a
rm -rf prebuilt/ios/OS
rm -rf prebuilt/ios/SIMULATOR64

cd build

# Arm64

rm -rf build
mkdir build
cd build

cmake .. -DCMAKE_TOOLCHAIN_FILE=$NDK_HOME/build/cmake/android.toolchain.cmake -DANDROID_ABI="arm64-v8a"
make

# Arm7

cd ..
rm -rf build
mkdir build
cd build

cmake .. -DCMAKE_TOOLCHAIN_FILE=$NDK_HOME/build/cmake/android.toolchain.cmake -DANDROID_ABI="armeabi-v7a"
make

# x86

cd ..
rm -rf build
mkdir build
cd build

cmake .. -DCMAKE_TOOLCHAIN_FILE=$NDK_HOME/build/cmake/android.toolchain.cmake -DANDROID_ABI="x86_64"
make

cd ..
rm -rf build