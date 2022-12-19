#! /bin/bash

make clean
make batt_update_asm.o
make hybrid_main
./hybrid_main 7578 P


