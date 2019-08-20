#!/bin/bash -eu

meson _build
ninja -C _build

$CC $CFLAGS -c -std=c99 -I. -I./c/include c/parse_markup_fuzzer.c -o $OUT/parse_markup_fuzzer
