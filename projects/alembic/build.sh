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
# cd ..

# build openexr for alembic
cd openexr
cmake .
make -j$(nproc)
make install
cd ..

# build alembic
cd alembic
mkdir build
cd build
cmake .. -DALEMBIC_SHARED_LIBS=OFF -DILMBASE_INCLUDE_DIR=/usr/local/include/OpenEXR \
-DILMBASE_ROOT=/usr/local/lib64
make clean
make -j$(nproc)
make install
# cd ../..
# cd include/OpenEXR
ls
# build fuzzers
# for fuzzers in $(find $SRC -name '*_fuzzer.cc'); do
#   fuzz_basename=$(basename -s .cc $fuzzers)
#   $CXX $CXXFLAGS -std=c++11 -Iinclude/ -I /usr/local/include/OpenEXR \
#   $fuzzers $LIB_FUZZING_ENGINE ./lib/Alembic/libAlembic.a \
#   -o $OUT/$fuzz_basename
# done

# Build dependencies
# export ALM_DEPS_PATH=$SRC/alm_deps
# mkdir -p $ALM_DEPS_PATH

# cd $SRC/openexr
# cmake . -DCMAKE_INSTALL_PREFIX=="$ALM_DEPS_PATH"
# make clean
# make -j$(nproc)
# make install

# cd /src/alm_deps
# ls

# cd $SRC/alembic
# cmake -DALEMBIC_SHARED_LIBS=OFF -DALEMBIC_SHARED_LIBS=OFF -DILMBASE_INCLUDE_DIR="$ALM_DEPS_PATH" \
# -DILMBASE_ROOT="ALM_DEPS_PATH"
# make -j$(nproc) clean
# make -j$(nproc) all

for fuzzers in $(find $SRC -name '*_fuzzer.cc'); do
  fuzz_basename=$(basename -s .cc $fuzzers)
  $CXX $CXXFLAGS -std=c++11 $fuzzers ./src/lib/libAlembic.a \
  $LIB_FUZZING_ENGINE  \
  -o $OUT/$fuzz_basename
done
