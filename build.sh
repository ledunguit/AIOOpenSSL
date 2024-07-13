#!/usr/bin/env sh

git submodule init

git submodule update

cd openssl || exit 1

./config no-shared

make -j10

cp -rf libcrypto.a libssl.a ../libs
mkdir -p ../includes/openssl
cp -r include/openssl/*.h ../includes/openssl

cd .. || exit 1
cd liboqs || exit 1

mkdir -p build && cd build || exit 1
cmake -GNinja ..
ninja

cp -rf lib/liboqs.a ../../libs
cp -r include/oqs ../../includes

cd ..

cd ..

cd oqs-provider || exit 1

cmake -S . -B build -DOQS_PROVIDER_BUILD_STATIC=ON && cmake --build build

cp -rf build/lib/liboqsprovider.a ../libs


