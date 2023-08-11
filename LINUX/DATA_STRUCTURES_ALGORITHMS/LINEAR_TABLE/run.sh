#!/bin/bash

cmake -B build

cmake --build build

./build/sequence_list_list
