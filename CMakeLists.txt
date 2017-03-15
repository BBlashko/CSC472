#------------------------------#
#CSC 472 - Assignment 1 - Setup
#------------------------------#
project(Modelling)
cmake_minimum_required(VERSION 3.0)

#------------------------------#
#Include atlas
#------------------------------#
add_subdirectory(atlas)
include_directories(${ATLAS_INCLUDE_DIRS})

add_subdirectory(assignment1)
add_subdirectory(assignment2)
add_subdirectory(assignment3)