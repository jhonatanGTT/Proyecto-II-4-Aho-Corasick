#!/bin/bash

SALIDA=texto_10mb.txt

rm -f $SALIDA

for ((i=0;i<655360;i++))
do
    echo -n "she his hers he " >> $SALIDA
done