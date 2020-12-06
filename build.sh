#!/bin/bash

g++ -c  main.cpp
g++ -c -fopenmp -fcilkplus -lcilkrts -pthread parallel.cpp
g++ -c  auxiliary.cpp
g++  -O3 -fopenmp -fcilkplus -lcilkrts -pthread -o parallelProgram main.o parallel.o auxiliary.cpp
#g++ -O3 -fopenmp -fcilkplus -lcilkrts -pthread -o parallelProgram main.o  auxiliary.cpp 
