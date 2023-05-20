#!/bin/sh
rm -rf build/
emcmake cmake -B build
pushd .
cd build
make
pushd .
cd bin
emrun --browser chrome index.html
popd
popd

