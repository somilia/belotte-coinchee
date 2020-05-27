cmake_minimum_required(VERSION 3.16)
project(ProjectIFB C)

set(CMAKE_C_STANDARD 99)


add_executable(ProjectIFB main.c carte.h joueur.h joueur.c equipe.c equipe.h contrat.c contrat.h menuenchere.c menuenchere.h carte.c carte.h)