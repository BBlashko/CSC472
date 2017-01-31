set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W4 -std=gnu++11")

file(GLOB_RECURSE SOURCES *.cpp)


add_executable(assignment1 src/main.cpp 
							src/BSplineScene.cpp 
							src/BSplineScene.h  
							src/ControlPoints.h 
							src/ControlPoints.cpp
							src/BSpline.h
							src/BSpline.cpp)
target_link_libraries(assignment1 ${ATLAS_LIBRARIES})

