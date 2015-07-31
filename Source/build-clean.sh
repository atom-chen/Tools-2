#!/bin/bash
#
# Windows 32-bit/64-bit

# Copyright (C) polynation games ltd - All Rights Reserved
# Unauthorized copying of this file, via any medium is strictly prohibited
# Proprietary and confidential
# Written by Christopher Redden, December 2013

# 62 Bit Version
rm -rf window/x86_64


cd ../pbc/
make clean

cd ../cjson/
make clean

cd ..
make clean