# Copyright 2020 Google Inc.
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

FROM gcr.io/oss-fuzz-base/base-builder
MAINTAINER greg.landrum@gmail.com

RUN apt-get update && apt-get upgrade -y && apt install -y \
  curl \
  wget \
  zlib1g-dev \
  libbz2-dev \
  git \
  g++ \
  make \
  libeigen3-dev \
  python3 \
  libpython3-all-dev \
  python3-pip \
  && cd /usr/local/bin \
  && ln -s /usr/bin/python3 python \
  && pip3 install --upgrade pip


# Install latest cmake
RUN wget https://github.com/Kitware/CMake/releases/download/v3.14.5/cmake-3.14.5-Linux-x86_64.sh; \
    chmod +x cmake-3.14.5-Linux-x86_64.sh; \
    ./cmake-3.14.5-Linux-x86_64.sh --skip-license --prefix="/usr/local"

# Install boost
WORKDIR /src
RUN wget --quiet -O boost.tar.bz2 https://sourceforge.net/projects/boost/files/boost/1.69.0/boost_1_69_0.tar.bz2/download && \
tar xjf boost.tar.bz2
# build boost
WORKDIR /src/boost_1_69_0
RUN ./bootstrap.sh --prefix="/usr/local/"  --with-libraries=iostreams,regex,serialization,system && \
./b2 -q install -j2 cxxflags="$CXXFLAGS $CXXFLAGS_EXTRA" toolset=clang

WORKDIR /src
RUN git clone --depth 1 https://github.com/rdkit/rdkit.git rdkit
WORKDIR rdkit
COPY build.sh *.cc $SRC/
