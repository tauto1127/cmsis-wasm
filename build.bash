#!/bin/bash

bash Third_Party/download.bash

mkdir build

cd build

cmake -D debug=true -D gcov=true ..

make

make install