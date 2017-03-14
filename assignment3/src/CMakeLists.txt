#------------------------------#
#CSC 472 - Assignment 1 - Setup
#------------------------------#
project(assignment3)

cmake_minimum_required(VERSION 3.0)
add_executable(assignment1 src/main.cxx
							src/LSystemScene.cpp
							src/LSystemScene.h
							src/PythagorasTree.cpp
							src/PythagorasTree.hpp)

#------------------------------#
#Include atlas
#------------------------------#
add_subdirectory(atlas)
include_directories(${ATLAS_INCLUDE_DIRS})
target_link_libraries(${APP_NAME} ${ATLAS_LIBRARIES})
