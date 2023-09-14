cmake_minimum_required(VERSION 3.25)
project(Lab1_2_3 C)

set(CMAKE_C_STANDARD 11)

add_executable(Lab1_2_3
        lab1-2-3.c
        Makefile
        chain.c
        chain.h init.c)
