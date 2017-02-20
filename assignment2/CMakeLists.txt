set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W4 -std=gnu++11")

file(GLOB_RECURSE SOURCES *.cpp)


add_executable(assignment2 src/main.cpp
						   src/Color.cpp
						   src/Color.hpp
						   src/LookupTables.hpp
						   src/Object.hpp
						   src/PolygonizationScene.hpp
						   src/PolygonizationScene.cpp
						   src/Polygonize.hpp
						   src/Polygonize.cpp
						   src/Sphere.hpp
						   src/Sphere.cpp)
target_link_libraries(assignment2 ${ATLAS_LIBRARIES})

