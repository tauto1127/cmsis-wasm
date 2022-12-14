#!/bin/bash

bash Third_Party/download.bash

cd cmake-build

cmake -D debug=true -D gcov=true ..

make