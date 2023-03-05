#!/bin/bash
SECONDS=0

pocetCasti=$1;
n=$2;
k=$3;
pocetBeziacich=$4
skupinyGrafov=$5;

for i in $(eval echo {1..${pocetCasti}}); do
  mkfifo graf-$i
  GenReg $n $k -e -a stdout -m $i $pocetCasti > graf-$i & 
  paralelneKostry graf-$i $n $k $pocetBeziacich $skupinyGrafov &
  #./build/bin/pocitanieKostier graf-$i $n $k $pocetBeziacich $skupinyGrafov &
done

wait

eval rm graf-{1..${pocetCasti}};

paralelneKostry out-graf $n $k $pocetCasti;

eval rm out-graf-{1..${pocetCasti}}.txt;

for i in $(eval echo {1..${pocetCasti}}); do
  subor=${n}_${k}_3#${i}.erg
  cat $subor >> maxMinReg${k}-${n}.txt
  rm $subor
done

echo "trvanie celeho spracovania je $SECONDS sekund" >> maxMinReg${k}-${n}.txt
echo "trvanie celeho spracovania je $SECONDS sekund";
exit 0;