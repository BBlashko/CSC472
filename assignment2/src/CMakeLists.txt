#------------------------------#
#CSC 472 - Assignment 1 - Setup
#------------------------------#
project(assignment2)

cmake_minimum_required(VERSION 3.0)
add_executable(assignment2 src/main.cxx)

#------------------------------#
#Include atlas
#------------------------------#
add_subdirectory(atlas)
include_directories(${ATLAS_INCLUDE_DIRS})
target_link_libraries(${APP_NAME} ${ATLAS_LIBRARIES})
