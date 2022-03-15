cmake_minimum_required(VERSION 3.10)
project(lab2) 

add_executable(clone clone.c pomiar_czasu.h pomiar_czasu.c)
add_executable(fork fork.c pomiar_czasu.h pomiar_czasu.c)
add_executable(prog prog.c)
