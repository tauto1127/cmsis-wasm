#!/bin/bash

bash Third_Party/download.bash

mkdir cmake-build

cd cmake-build

cmake -D debug=true -D gcov=true ..

make

make install