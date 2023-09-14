cmake_minimum_required(VERSION 3.25)
project(Lab2_PCM C)

set(CMAKE_C_STANDARD 23)

add_executable(Lab2_PCM lab2.c
                Makefile
                mypcm.h
                mypcm.c)
