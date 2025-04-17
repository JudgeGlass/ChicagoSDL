#!/bin/bash

rm -r libchicagosdl-dev.a
cd ..
make lib -j4
cd test
cp ../lib/libchicagosdl-dev.a .
g++ -c main.cpp -I../include -o main.o
g++ main.o -o main -L. -l:libchicagosdl-dev.a -lSDL2main -lSDL2 -lSDL2_image
rm -r main.o