#!/bin/sh
VER="0.5"
CURRDIR=`pwd`
DISTDIR=../qcat-dist-$VER
mkdir "$DISTDIR"
mkdir "$DISTDIR/bin"
mkdir "$DISTDIR/build"
mkdir "$DISTDIR/src"
mkdir "$DISTDIR/icons"

cp -r icons $DISTDIR
cp -r src $DISTDIR
cp qcat.pro COPYING README INSTALL $DISTDIR
