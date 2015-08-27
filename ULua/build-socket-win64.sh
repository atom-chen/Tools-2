#!/bin/bash
#
# Windows 32-bit/64-bit

# Copyright (C) polynation games ltd - All Rights Reserved
# Unauthorized copying of this file, via any medium is strictly prohibited
# Proprietary and confidential
# Written by Christopher Redden, December 2013

# 62 Bit Version
mkdir -p window/x86_64

cd luajit
mingw32-make clean

mingw32-make BUILDMODE=static CC="gcc -m64"
cp src/libluajit.a ../window/x86_64/libluajit.a

cd ..

gcc luasocket/src/luasocket.c \
    luasocket/src/timeout.c \
    luasocket/src/buffer.c \
    luasocket/src/io.c \
    luasocket/src/auxiliar.c \
    luasocket/src/options.c \
    luasocket/src/inet.c \
    luasocket/src/tcp.c \
    luasocket/src/udp.c \
    luasocket/src/except.c \
    luasocket/src/select.c \
    luasocket/src/wsocket.c \
	luasocket/src/mime.c \
    -o Plugins/x86_64/socketcore.dll -m64 -shared \
    -I./ \
    -Iluajit/src \
    -Iluasocket/src \
    -Wl,--whole-archive \
    window/x86_64/libluajit.a \
    -Wl,--no-whole-archive -lwsock32 -static-libgcc -static-libstdc++