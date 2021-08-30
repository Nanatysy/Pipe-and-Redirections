cmake_minimum_required(VERSION 3.20)
project(pipex C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(pipex
        ft_calloc.c
        ft_split.c
        ft_strdup.c
        ft_strlen.c
        main.c
        error.c
        pipex.h)
