#!/bin/sh
rm -rf build/
sleep 1
cmake -B build
pushd .
cd build
make
pushd .
cd bin
./fluffy
popd
popd

