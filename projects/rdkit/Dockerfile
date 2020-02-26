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
  libeigen3-dev \
  python3 \
  libpython3-all-dev \
  python3-numpy \
  python3-pip \
  python3-pil \
  python3-pandas
RUN git clone --depth 1 https://github.com/rdkit/rdkit.git rdkit
WORKDIR rdkit
COPY build.sh $SRC/
