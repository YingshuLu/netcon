#!/bin/sh

PRODUCT=netcon
WORKPATH=/usr/$PRODUCT
INIPATH=$WORKPATH/etc
LOGPATH=$WORKPATH/log
BINPATH=$WORKPATH/bin
LIBPATH=$WORKPATH/lib

INIFILE=$PRODUCT.ini
EXEFILE=$PRODUCT

INSTALLED=0

makePath()
{
	mkdir -p $INIPATH
	mkdir -p $LOGPATH
	mkdir -p $BINPATH
	mkdir -p $LIBPATH
}

rmPath
{
	rm -fr $INIPATH
	rm -fr $LOGPATH
	rm -fr $BINPATH
	rm -fr $LIBPATH
}

copyFile()
{
	cp $EXEFILE $BINPATH/
	cp $INIFILE $INIPATH/
	cp *.so $LIBPATH/
}

installed()
{
	[ -f $BINFILE ] && [ -f $INIFILE] && INSTALLED=1
}
#main
[ $# -eq 0] && action="install"
[ $# -gt 0 ] && action="$1"

install

[ "$action" == "install" ] && [ $INSTALLED -eq 0] && makePath && copyFile

[ "$action" == "uninstall" ] && rmPath 

exit 0
