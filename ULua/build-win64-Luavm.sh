#!/bin/bash
#
# Windows 32-bit/64-bit

# Copyright (C) polynation games ltd - All Rights Reserved
# Unauthorized copying of this file, via any medium is strictly prohibited
# Proprietary and confidential
# Written by Christopher Redden, December 2013

# 62 Bit Version
mkdir -p window/x86_64

cd lua-5.1.5/src
mingw32-make -fMakefile-Static clean

mingw32-make -fMakefile-Static BUILDMODE=static CC="gcc -m64"
cp liblua.a ../../window/x86_64/liblua.a

cd ../..

gcc lua_wrap.c \
    -o Plugins/x86_64/ulua.dll -m64 -shared \
    -I./ \
    -Ilua-5.1.5/src \
    -Wl,--whole-archive \
    window/x86_64/liblua.a \
    -Wl,--no-whole-archive -lwsock32 -static-libgcc -static-libstdc++
