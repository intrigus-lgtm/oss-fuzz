#!/bin/bash -eu

# configure script needs leak checking disabled to not fail
export ASAN_OPTIONS=detect_leaks=0

# Build a recent version of harbfuzz
cd harfbuzz
./autogen.sh 
./configure --with-freetype=yes --with-gobject=yes
make
make install
cd -

cd pango
build=$WORK/build

# cleanup
rm -rf $build
mkdir -p $build

sed -i "/'-Werror=implicit-fallthrough',/d" meson.build

CFLAGS="${CFLAGS} -Wno-implicit-fallthrough" meson $build \
  -Db_lundef=false  \
  -Dgtk_doc=false \
  -Dinstall-tests=false \
  #-Dintrospection=false  \


ninja -C $build 
ninja -C $build install

export GLIB_CFLAGS="$(pkg-config --static --cflags glib-2.0)"
export HB_CFLAGS="$(pkg-config --static --cflags harfbuzz)"
export CAIRO_CFLAGS="$(pkg-config --static --cflags cairo)"
export PANGO_CFLAGS="$(pkg-config --static --cflags pango)"
export GLIB_LIBS="$(pkg-config --static --libs glib-2.0)"
export HB_LIBS="$(pkg-config --static --libs harfbuzz)"
export CAIRO_LIBS="$(pkg-config --static --libs cairo)"
export PANGO_LIBS="$(pkg-config --static --libs pango)"

$CC $CFLAGS \
  -I. -I$build/pango/ -I$build -I./c/include ${GLIB_CFLAGS} ${HB_CFLAGS} ${CAIRO_CFLAGS} ${PANGO_CFLAGS}\
  ${LIB_FUZZING_ENGINE} \
  ${GLIB_LIBS} ${HB_LIBS} ${CAIRO_LIBS} ${PANGO_LIBS}\
  ../parse_markup_fuzzer.c -o $OUT/parse_markup_fuzzer
chmod +x $OUT/parse_markup_fuzzer
$OUT/parse_markup_fuzzer
