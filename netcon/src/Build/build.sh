#!/bin/sh

cwd=`pwd`
makefile="Makefile"
cd ../
echo "Pre-buid: clean all old file"
make cleanall -f $makefile
make -f $makefile
make clean -f $makefile
cd $cwd
