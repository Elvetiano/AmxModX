#!/bin/bash

# AMX Mod X
#
# by the AMX Mod X Development Team
#  originally developed by OLO
#
# This file is part of AMX Mod X.

# new code contributed by \malex\
 
function compilex {
test -e compiled || mkdir compiled 2> /dev/null
test -e ../plugins || mkdir ../plugins 2> /dev/null
rm -r NUL 2> /dev/null
rm -f temp.txt 2> /dev/null
#read  -p "This will compile all sma files, press Enter to start"
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


for f in *; do mv "$f" `echo $f | tr ' ' '_'`; done

for sourcefile in *.sma
do
        amxxfile="`echo $sourcefile | sed -e 's/\.sma$/.amxx/'`"
        echo -n "Compiling $sourcefile ..."; 		
        $pc $sourcefile -ocompiled/$amxxfile  >> temp.txt
        echo "done"
done
read -t 5 -p "Moving compiled to plugins folder ..."
echo
echo
cp compiled/* ../plugins/
read -t 2 -p "Job Done - Press ENTER = main menu"
rm temp.txt
echo
}


      E='echo -e';e='echo -en';trap "R;exit" 2
    ESC=$( $e "\e")
   TPUT(){ $e "\e[${1};${2}H";}
  CLEAR(){ $e "\ec";}
  CIVIS(){ $e "\e[?25l";}
   DRAW(){ $e "\e%@\e(0";}
  WRITE(){ $e "\e(B";}
   MARK(){ $e "\e[7m";}
 UNMARK(){ $e "\e[27m";}
      R(){ CLEAR ;stty sane;$e "\ec\e[37;44m\e[J";};
   HEAD(){ DRAW
           for each in $(seq 1 13);do
           $E "   x                                          x"
           done
           WRITE;MARK;TPUT 1 5
           $E "BASH SELECTION MENU                       ";UNMARK;}
           i=0; CLEAR; CIVIS;NULL=/dev/null
   FOOT(){ MARK;TPUT 13 5
           printf "ENTER - SELECT,NEXT                       ";UNMARK;}
  ARROW(){ read -s -n3 key 2>/dev/null >&2
           if [[ $key = $ESC[A ]];then echo up;fi
           if [[ $key = $ESC[B ]];then echo dn;fi;}
     M0(){ TPUT  4 20; $e "Delete Compiled folders!";}
     M1(){ TPUT  5 20; $e "Compile";}
     #M2(){ TPUT  6 20; $e "Disk";}
     #M3(){ TPUT  7 20; $e "Routing";}
     #M4(){ TPUT  8 20; $e "Time";}
     #M5(){ TPUT  9 20; $e "ABOUT  ";}
     M2(){ TPUT 6 20; $e "EXIT   ";}
      LM=2
   MENU(){ for each in $(seq 0 $LM);do M${each};done;}
    POS(){ if [[ $cur == up ]];then ((i--));fi
           if [[ $cur == dn ]];then ((i++));fi
           if [[ $i -lt 0   ]];then i=$LM;fi
           if [[ $i -gt $LM ]];then i=0;fi;}
REFRESH(){ after=$((i+1)); before=$((i-1))
           if [[ $before -lt 0  ]];then before=$LM;fi
           if [[ $after -gt $LM ]];then after=0;fi
           if [[ $j -lt $i      ]];then UNMARK;M$before;else UNMARK;M$after;fi
           if [[ $after -eq 0 ]] || [ $before -eq $LM ];then
           UNMARK; M$before; M$after;fi;j=$i;UNMARK;M$before;M$after;}
   INIT(){ R;HEAD;FOOT;MENU;}
     SC(){ REFRESH;MARK;$S;$b;cur=`ARROW`;}
     ES(){ MARK;$e "ENTER = main menu ";$b;read;INIT;};INIT
  while [[ "$O" != " " ]]; do case $i in
        0) S=M0;SC;if [[ $cur == "" ]];then R; test -d "compiled" && echo "             Folders deleted !" || echo "             Folders already deleted !"; $e "\n$(rm -r compiled ../plugins  2> /dev/null)\n"; ES;fi;;
        1) S=M1;SC;if [[ $cur == "" ]];then R; TPUT 5 20; MARK; $e "COMPILING...please wait!";UNMARK; echo; compilex; ES;fi;;
        #2) S=M2;SC;if [[ $cur == "" ]];then R;$e "\n$(df -h    )\n";ES;fi;;
        #3) S=M3;SC;if [[ $cur == "" ]];then R;$e "\n$(route -n )\n";ES;fi;;
        #4) S=M4;SC;if [[ $cur == "" ]];then R;$e "\n$(date     )\n";ES;fi;;
        #5) S=M5;SC;if [[ $cur == "" ]];then R;$e "\n$($e by oTo)\n";ES;fi;;
        2) S=M2;SC;if [[ $cur == "" ]];then R;exit 0;fi;;
 esac;POS;done

#echo
#echo
#read -t 1 -p "Press Q to close" >> temp.txt
#echo " " >> temp.txt
#echo "Press Q to close" >> temp.txt
#less temp.txt
#rm temp.txt
#sleep 5
#kill $$

