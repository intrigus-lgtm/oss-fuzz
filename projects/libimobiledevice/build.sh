#!/bin/bash -eu
# Copyright 2019 Google Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
################################################################################

# build project
# libplist
(
cd libplist
./autogen.sh --without-cython --enable-debug
make
sudo make install
)

#libusbmuxd
(
cd libusbmuxd
./autogen.sh --without-cython --enable-debug
make
sudo make install
)

#gnutls
(
cd gnutls
./bootstrap
./configure
make
make check
)

#libimobiledevice
cd libimobiledevice
./autogen.sh --disable-openssl
sudo make install

find . -name "*.a"

# build fuzzers
# e.g.
# $CXX $CXXFLAGS -std=c++11 -Iinclude \
#     /path/to/name_of_fuzzer.cc -o $OUT/name_of_fuzzer \
#     $LIB_FUZZING_ENGINE /path/to/library.a
