# Copyright 2016 Google Inc.
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
MAINTAINER eustas@chromium.org
RUN apt-get update && apt-get install -y \
			cmake \
			libffi-dev \
			libfribidi-dev \
			libglib2.0-dev \
			libmount-dev \
			libpcre2-dev \
			libthai-dev \
			libxml2-utils \
			mount \
			python3-pip \
			autoconf automake libtool pkg-config ragel \
			libfontconfig1-dev \
			libfreetype6-dev libglib2.0-dev libcairo2-dev \
			gobject-introspection \
			libgirepository1.0-dev 

RUN pip3 install meson cffi ninja

RUN git clone --depth 1 https://github.com/harfbuzz/harfbuzz
RUN git clone --depth 1 https://gitlab.gnome.org/GNOME/pango
COPY parse_markup_fuzzer.c $SRC/
COPY build.sh $SRC/
