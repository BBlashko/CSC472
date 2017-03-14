set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W4 -std=gnu++11")

file(GLOB_RECURSE SOURCES *.cpp)


add_executable(assignment3 src/main.cpp
							src/LSystemScene.cpp
							src/LSystemScene.hpp
							src/PythagorasTree.cpp
							src/PythagorasTree.hpp)
target_link_libraries(assignment3 ${ATLAS_LIBRARIES})
