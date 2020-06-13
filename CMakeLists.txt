cmake_minimum_required(VERSION 3.16)
project(ProjectIFB C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_BUILD_TYPE RelWithDebInfo)

SET(CMAKE_CXX_FLAGS_DEBUG "-O0")
SET(CMAKE_C_FLAGS_DEBUG "-O0")

add_executable(ProjectIFB main.c carte.h joueur.h joueur.c equipe.c equipe.h carte.c carte.h jeu.h jeu.c common.h enchere.h enchere.c pli.h pli.c annonce.c annonce.h sauvegarde.c sauvegarde.h)