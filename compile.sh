#!/bin/bash

WAMR_ROOT=/home/sora/test/wasm-thread/wasm-micro-runtime-WAMR-1.1.1
CURR_DIR=$PWD
SOURCE=${CURR_DIR}/src

/home/sora/test/wasi-sdk-16.0/bin/clang -pthread -O3  \
    -Wl,--shared-memory,--max-memory=196608           \
    -Wl,--allow-undefined,--no-check-features         \
    -Wl,--export=__heap_base,--export=__data_end      \
    -Wl,--export-all                                  \
    -I ${SOURCE}/config                               \
    -I ${SOURCE}/core                                 \
    -I ${CURR_DIR}/public/include                     \
    ${SOURCE}/core/*wasm*.c ${SOURCE}/api/cmsis*.c    \
    ${CURR_DIR}/test/testapp.cpp -o cmsis_wasm_prot.wasm