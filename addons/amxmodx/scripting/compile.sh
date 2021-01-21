#!/bin/bash

# AMX Mod X
#
# by the AMX Mod X Development Team
#  originally developed by OLO
#
# This file is part of AMX Mod X.

# new code contributed by \malex\

test -e compiled || mkdir compiled 2> /dev/null
test -e ../plugins || mkdir ../plugins 2> /dev/null
rm -r NUL 2> /dev/null
rm -f temp.txt 2> /dev/null
read -p "This will compile all sma files, press Enter to start"
OS=`uname`-s 2> /dev/null

case $OS in 
  'Linux')
    pc=./amxxpc32.so
    ;;
  'FreeBSD')
    pc=./amxxpc32.so
    ;;
  'CYGWIN'*|'MINGW32'*|'MSYS'*|'MINGW'*|'Windows_NT')
	pc=./amxxpc.exe
    ;;
  'Darwin') 
	pc=./amxxpc_osx
    ;;
	*) 
	echo "UNKNOWN: $OS"
	;;
  *) ;;
esac

for sourcefile in *.sma
do
        amxxfile="`echo $sourcefile | sed -e 's/\.sma$/.amxx/'`"
        echo -n "Compiling $sourcefile ..."		
        $pc $sourcefile -ocompiled/$amxxfile >> temp.txt
        echo "done"
done
read -t 5 -p "Moving compiled to plugins folder ..."
echo
echo
cp compiled/* ../plugins/
read -p "Job Done - Press Enter to close"
echo
echo
#read -t 1 -p "Press Q to close" >> temp.txt
echo " " >> temp.txt
echo "Press Q to close" >> temp.txt
less temp.txt
rm temp.txt
sleep 5
kill $$

