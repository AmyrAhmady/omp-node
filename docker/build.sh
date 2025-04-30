#!/bin/bash

# Available configs: Debug, [RelWithDebInfo], Release, MinSizeRel
[[ -z "$CONFIG" ]] \
&& config=RelWithDebInfo \
|| config="$CONFIG"

[[ -z "$TARGET_BUILD_ARCH" ]] \
&& target_build_arch=x64 \
|| target_build_arch="$TARGET_BUILD_ARCH"

echo "TARGET_BUILD_ARCH=${TARGET_BUILD_ARCH}"
echo "target_build_arch=${target_build_arch}"

docker build \
    -t omp-node/build:ubuntu-18.04 ./ \
|| exit 1

folders=('build')
for folder in "${folders[@]}"; do
    if [[ ! -d "./${folder}" ]]; then
        mkdir ${folder}
    fi
    sudo chown -R 1000:1000 ${folder} || exit 1
done

docker run \
    --rm \
    -t \
    -w /code \
    -v $PWD/..:/code \
    -v $PWD/build:/code/build \
    -e CONFIG=${config} \
    -e TARGET_BUILD_ARCH=${target_build_arch} \
    omp-node/build:ubuntu-18.04
