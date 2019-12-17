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

FROM gcr.io/oss-fuzz-base/base-builder
MAINTAINER miller.lucas@gmail.com
RUN apt-get update && apt-get install -y build-essential python cmake make automake libtool curl
# OpenEXR
ARG OPENEXR_ROOT=/opt/openexr
ARG OPENEXR_VER=2.3.0
WORKDIR ${OPENEXR_ROOT}
RUN curl -O -L https://github.com/openexr/openexr/releases/download/v${OPENEXR_ROOT}/${OPENEXR_ROOT}.tar.gz && \
    tar -xvzf openexr-${OPENEXR_VER}.tar.gz && \
    cd openexr-${OPENEXR_VER} && \
    # enable gcc 7
    source /opt/rh/devtoolset-7/enable && \
    # IlmBase
    cd IlmBase && \
    ./bootstrap && \
    ./configure && \
    make && \
    make install && \
    # OpenEXR
    cd ../OpenEXR && \
    ./bootstrap && \
    ./configure && \
    make && \
    make install
RUN rm -rf ${OPENEXR_ROOT}
RUN git clone --depth 1 https://github.com/alembic/alembic alembic
WORKDIR alembic
COPY build.sh alembic_fuzzer.cc *.h $SRC/
