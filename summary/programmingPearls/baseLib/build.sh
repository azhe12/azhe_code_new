#!/bin/bash
TOP=$(pwd)
SRCDIR=$TOP/src
LIBDIR=$TOP/lib
INCDIR=$TOP/include
LIBNAME=baseLib
HEADER=${LIBNAME}.h
LIB=lib${LIBNAME}.so

cd $SRCDIR
make

cp $HEADER $INCDIR
cp $LIB $LIBDIR
