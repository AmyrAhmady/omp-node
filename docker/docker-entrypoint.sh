#!/bin/sh
[ -z $CONFIG ] && config=Release || config="$CONFIG"
[ -z $TARGET_BUILD_ARCH ] && target_build_arch=x64 || target_build_arch="$TARGET_BUILD_ARCH"

cmake --version

cmake \
    -S . \
    -B build \
    -G Ninja \
    -DCMAKE_BUILD_TYPE=$config \
    -DTARGET_BUILD_ARCH=${target_build_arch} \
&&
cmake \
    --build build \
    --config $config \
    --parallel $(nproc)
