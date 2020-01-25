#!/usr/bin/bash

for i in 0 10 20
do
    j=$(( $i + 9 ))
    (sleep 0.5 && echo $i $j && seq $i $j | nc 127.0.0.1 9000 -N) &
done
