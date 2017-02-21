#pragma once
#include "atlas/math/Math.hpp"
#include "Sphere.hpp"
#include <vector>

#define ISO_VALUE	    0.5f
#define MAX_FIELD_VALUE 1.0f
#define MIN_FIELD_VALUE 0.0f

namespace assignment2
{
    using Vector3 = atlas::math::Vector;

    struct Voxel
    {
        Vector3 cornerPositions[8];
        float cornerValue[8];
    };

    //struct Grid
    //{
    //    std::vector<Voxel> voxels;
    //};

    class MarchingCubes
    {
        using Vector3 = atlas::math::Vector;

        public:
            MarchingCubes::MarchingCubes(std::vector<Sphere> &SceneSpheres);
            void MarchingCubes::GenerateGrid(std::vector<Sphere>& SceneSpheres);
            void MarchingCubes::PolygonizeVoxel(Voxel cubeContainer, std::vector<Vector3> &Vertices, double isoLevel);

        private:
            std::vector<Voxel> SceneVoxels;
    };
}