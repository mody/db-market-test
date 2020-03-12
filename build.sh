#!/bin/sh

set -ex

[ ! -d build ] && mkdir build

cd build && cmake .. && make -j && ctest
