#!/bin/bash
# Script de benchmark para el proyecto Aho-Corasick paralelo (Pthreads)
# Uso: bash benchmark.sh
# Genera un archivo de 10MB y mide el tiempo con 1, 2 y 4 hilos, 5 repeticiones cada uno.

ARCHIVO=texto_10mb.txt

if [ ! -f "$ARCHIVO" ]; then
    echo "Generando archivo de prueba de 10MB..."
    bash gen1.sh
fi

echo "Hilos,Repeticion,Tiempo(s),Coincidencias"
for hilos in 1 2 4; do
    for rep in 1 2 3 4 5; do
        salida=$(./aho "$ARCHIVO" "$hilos")
        tiempo=$(echo "$salida" | grep "Tiempo" | awk '{print $2}')
        coincidencias=$(echo "$salida" | grep "Coincidencias" | awk '{print $3}')
        echo "$hilos,$rep,$tiempo,$coincidencias"
    done
done
