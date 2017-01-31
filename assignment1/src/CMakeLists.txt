#------------------------------#
#CSC 472 - Assignment 1 - Setup
#------------------------------#
project(assignment1)

cmake_minimum_required(VERSION 3.0)
add_executable(assignment1 src/main.cxx
							src/BSplineScene.cpp
							src/BSplineScene.h)

#------------------------------#
#Include atlas
#------------------------------#
add_subdirectory(atlas)
include_directories(${ATLAS_INCLUDE_DIRS})
target_link_libraries(${APP_NAME} ${ATLAS_LIBRARIES})
