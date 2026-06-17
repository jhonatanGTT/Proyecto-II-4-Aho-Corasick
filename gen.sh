#!/bin/bash

SALIDA=texto_1mb.txt

rm -f $SALIDA

for ((i=0;i<65536;i++))
do
    echo -n "she his hers he " >> $SALIDA
done