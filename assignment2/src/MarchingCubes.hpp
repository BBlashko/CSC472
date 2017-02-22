#pragma once
#include "atlas/math/Math.hpp"
#include "Sphere.hpp"
#include <vector>

#define ISO_VALUE	    0.5f
#define VOXEL_SIZE      0.1f

namespace assignment2
{
    using Vector3 = atlas::math::Vector;
    using Normal = atlas::math::Normal;

    struct Voxel
    {
        Vector3 cornerPositions[8];
        float cornerValue[8];
    };

    struct Grid
    {
        std::vector<Voxel> voxels;
        Vector3 boundingBox[8];
        int xSize;
        int ySize;
        int zSize;
    };

    class MarchingCubes
    {
        using Vector3 = atlas::math::Point;

        public:
            MarchingCubes::MarchingCubes() {};
            MarchingCubes::MarchingCubes(std::vector<Sphere*>& sceneSpheres)
            {
                mSceneSpheres = sceneSpheres;
            }

            int MarchingCubes::generateGrid();
            void MarchingCubes::createMesh(std::vector<Sphere*>& sceneSpheres, std::vector<Vector3> & vertices, std::vector<Normal> &normals);
            void MarchingCubes::polygonizeVoxel(Voxel cubeContainer, std::vector<Vector3> &Vertices, std::vector<Normal> &normals, float isoLevel);
            void MarchingCubes::calculateVertexValues(float *vertexArray, int y);
            void MarchingCubes::calculateVoxels(float *bottomVertexArray, float *topVertexArray, int y, std::vector<Vector3> & vertices, std::vector<Normal> &normals);

        private:
            
            Vector3 vertexLinearInterp(const Vector3 &p1, const Vector3 &p2, float valueP1, float valueP2);

            std::vector<Voxel> mSceneVoxels;
            Grid mSceneGrid;
            std::vector<Sphere*> mSceneSpheres;
    };
}