#pragma once
#include "atlas/math/Math.hpp"
#include "Sphere.hpp"
#include <vector>

#define ISO_VALUE	    0.5f
#define MAX_FIELD_VALUE 1.0f
#define MIN_FIELD_VALUE 0.0f
#define VOXEL_SIZE 1.0f

namespace assignment2
{
    using Vector3 = atlas::math::Vector;
    using Vector2 = atlas::math::Vector2;

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
        using Vector3 = atlas::math::Vector;

        public:
            MarchingCubes::MarchingCubes(std::vector<Sphere*> &SceneSpheres);
            int MarchingCubes::generateGrid();
            void MarchingCubes::createMesh();
            void MarchingCubes::polygonizeVoxel(Voxel cubeContainer, std::vector<Vector3> &Vertices, double isoLevel);
            void MarchingCubes::calculateVertexValues(float *vertexArray, int y);
            void MarchingCubes::calculateVoxels(float * bottomVertexArray, float * topVertexArray, int y, std::vector<Vector3> & vertices);

        private:
            
            Vector3 vertexLinearInterp(const Vector3 &p1, const Vector3 &p2, float valueP1, float valueP2);

            std::vector<Voxel> mSceneVoxels;
            Grid mSceneGrid;
            std::vector<Sphere*>& mSceneSpheres;
    };
}