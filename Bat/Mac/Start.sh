#!/bin/sh

#echo 'hello world'

FULL_FILE_PATH=$0
echo "FULL_FILE_PATH"
echo ${FULL_FILE_PATH}

FULL_FILE_NAME=$(basename "${FULL_FILE_PATH}")
echo "FULL_FILE_NAME"
echo ${FULL_FILE_NAME}

REL_BASE_DIR=`dirname ${FULL_FILE_PATH}`
echo "BASE_DIR"
echo ${BASE_DIR}

ABS_BASE_DIR=`pwd`
echo "ABS_BASE_DIR"
echo ${ABS_BASE_DIR}

FILE_NAME_NOALLEXT="${FULL_FILE_NAME%%.*}"
echo "FILE_NAME_NOALLEXT"
echo ${FILE_NAME_NOALLEXT}

FILE_NAME_NOEXT="${FULL_FILE_NAME%.*}"
echo "FILE_NAME_NOEXT"
echo ${FILE_NAME_NOEXT}

FILE_ALL_EXT_NAME="${FULL_FILE_NAME#*.}"
echo "FILE_ALL_EXT_NAME"
echo ${FILE_ALL_EXT_NAME}

FILE_EXT_NAME="${FULL_FILE_NAME##*.}"
echo "FILE_EXT_NAME"
echo ${FILE_EXT_NAME}


cd ${ABS_BASE_DIR}

ToolSet=${ABS_BASE_DIR}
PyLibs=${ABS_BASE_DIR}/../../PyLibs/src
export PYTHONPATH=${PYTHONPATH}:${ToolSet}:${PyLibs}

Python=/Library/Frameworks/Python.framework/Versions/3.5/bin/python3.5

cd ./QtToolSet
${Python} ./Main.py

#cd -