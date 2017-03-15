set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W4 -std=gnu++11")

file(GLOB_RECURSE SOURCES *.cpp)


add_executable(assignment2 src/main.cpp
						   src/PolygonizationScene.hpp
						   src/PolygonizationScene.cpp
						   src/Sphere.hpp
						   src/Sphere.cpp
						   src/LookupTables.hpp
						   src/MarchingCubes.cpp
						   src/MarchingCubes.hpp
						   src/Mesh.cpp
						   src/Mesh.hpp)
target_link_libraries(assignment2 ${ATLAS_LIBRARIES})

