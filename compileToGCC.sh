#!/bin/bash

rm -rf gcc
mkdir gcc

# copy all files from src to gcc folder 
cp src/**/*.* gcc
cp src/*.* gcc
cp -R lib gcc
   
#g++ gcc/*.cpp -std=c++17 -I lib -I /usr/local/Cellar/boost/1.66.0 -o satnew
#g++ gcc/*.cpp -std=c++17 -I lib -I /usr/include/boost -o sat
