#!/bin/sh
#
#  build.command
#  svg_rasterizer
#
#  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 25.07.2020.
#  Copyright © 2020 Dmitrii Torkhov. All rights reserved.
#

if [ -z "$NDK_HOME" ]
then
      echo "NDK_HOME is empty"
      exit
fi

cd "$(dirname "$0")"

rm -rf prebuilt

#######
# iOS #
#######

# Arm

rm -rf build

cmake -S . -B build \
	-DCMAKE_ARCHIVE_OUTPUT_DIRECTORY=$(dirname "$0")/prebuilt/ios/arm \
	-DCMAKE_TOOLCHAIN_FILE=toolchains/ios.toolchain.cmake \
	-DCMAKE_BUILD_TYPE=Release \
	-DPLATFORM="OS" \
	-DDEPLOYMENT_TARGET="11.0" \
	-DENABLE_BITCODE=FALSE \
	-DENABLE_ARC=FALSE \
	-DENABLE_VISIBILITY=FALSE \
	-DENABLE_STRICT_TRY_COMPILE=FALSE
cmake --build build -j 4

# x86

rm -rf build

cmake -S . -B build \
	-DCMAKE_ARCHIVE_OUTPUT_DIRECTORY=$(dirname "$0")/prebuilt/ios/x86 \
	-DCMAKE_TOOLCHAIN_FILE=toolchains/ios.toolchain.cmake \
	-DCMAKE_BUILD_TYPE=Release \
	-DPLATFORM="SIMULATOR64" \
	-DDEPLOYMENT_TARGET="11.0" \
	-DENABLE_BITCODE=FALSE \
	-DENABLE_ARC=FALSE \
	-DENABLE_VISIBILITY=FALSE \
	-DENABLE_STRICT_TRY_COMPILE=FALSE
cmake --build build -j 4

# Fat

lipo -create prebuilt/ios/arm/libsvg.a prebuilt/ios/x86/libsvg.a -output prebuilt/ios/libsvg.a
rm -rf prebuilt/ios/arm
rm -rf prebuilt/ios/x86

###########
# Android #
###########

# Arm64

rm -rf build

cmake -S . -B build \
	-DCMAKE_ARCHIVE_OUTPUT_DIRECTORY=$(dirname "$0")/prebuilt/android/arm64-v8a \
	-DCMAKE_TOOLCHAIN_FILE=$NDK_HOME/build/cmake/android.toolchain.cmake \
	-DCMAKE_BUILD_TYPE=Release \
	-DANDROID_PLATFORM=21 \
	-DANDROID_ABI="arm64-v8a"
cmake --build build -j 4

# Arm

rm -rf build

cmake -S . -B build \
	-DCMAKE_ARCHIVE_OUTPUT_DIRECTORY=$(dirname "$0")/prebuilt/android/armeabi-v7a \
	-DCMAKE_TOOLCHAIN_FILE=$NDK_HOME/build/cmake/android.toolchain.cmake \
	-DCMAKE_BUILD_TYPE=Release \
	-DANDROID_PLATFORM=21 \
	-DANDROID_ABI="armeabi-v7a"
cmake --build build -j 4

# x86

rm -rf build

cmake -S . -B build \
	-DCMAKE_ARCHIVE_OUTPUT_DIRECTORY=$(dirname "$0")/prebuilt/android/x86 \
	-DCMAKE_TOOLCHAIN_FILE=$NDK_HOME/build/cmake/android.toolchain.cmake \
	-DCMAKE_BUILD_TYPE=Release \
	-DANDROID_PLATFORM=21 \
	-DANDROID_ABI="x86_64"
cmake --build build -j 4

# Cleanup

rm -rf build