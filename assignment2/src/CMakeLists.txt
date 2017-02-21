#------------------------------#
#CSC 472 - Assignment 1 - Setup
#------------------------------#
project(assignment2)

#------------------------------#
#Include atlas
#------------------------------#
add_subdirectory(atlas)
include_directories(${ATLAS_INCLUDE_DIRS})
target_link_libraries(${APP_NAME} ${ATLAS_LIBRARIES})