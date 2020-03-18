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
  libboost-all-dev \
  cmake \
  git \
  g++ \
  make \
  libeigen3-dev \
  python3 \
  libpython3-all-dev \
  python3-numpy \
  python3-pip \
  python3-pil \
  python3-pandas \
  && cd /usr/local/bin \
  && ln -s /usr/bin/python3 python \
  && pip3 install --upgrade pip


# Install latest cmake.
RUN wget https://github.com/Kitware/CMake/releases/download/v3.14.5/cmake-3.14.5-Linux-x86_64.sh; \
    chmod +x cmake-3.14.5-Linux-x86_64.sh; \
    ./cmake-3.14.5-Linux-x86_64.sh --skip-license --prefix="/usr/local"

RUN git clone --depth 1 https://github.com/rdkit/rdkit.git rdkit
WORKDIR rdkit
COPY build.sh *.cc $SRC/
