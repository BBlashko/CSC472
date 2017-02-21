#pragma once
#include "MarchingCubes.hpp"
#include "LookupTables.hpp"
#include <math.h>

namespace assignment2
{
    MarchingCubes::MarchingCubes(std::vector<Sphere>& SceneSpheres)
    {
        GenerateGrid(SceneSpheres);
    }

    void MarchingCubes::GenerateGrid(std::vector<Sphere>& SceneSpheres)
    {
        //TODO: LIMIT THE GRID AND VOXEL SIZE
        int minX, minY, minZ, maxX, maxY, maxZ;
        //for (int i = 0; SceneSpheres.size(); i++)
        //{

        //}

        Voxel BoundingBox;
    }

    void MarchingCubes::PolygonizeVoxel(Voxel voxel, std::vector<Vector3> &vertices, double isoLevel)
    {
        int voxelIndex = 0;
        std::vector<Vector3> vertexList;

        if (voxel.cornerValue[0] < 0.0f) voxelIndex |= 1;
        if (voxel.cornerValue[1] < 0.0f) voxelIndex |= 2;
        if (voxel.cornerValue[2] < 0.0f) voxelIndex |= 4;
        if (voxel.cornerValue[3] < 0.0f) voxelIndex |= 8;
        if (voxel.cornerValue[4] < 0.0f) voxelIndex |= 16;
        if (voxel.cornerValue[5] < 0.0f) voxelIndex |= 32;
        if (voxel.cornerValue[6] < 0.0f) voxelIndex |= 64;
        if (voxel.cornerValue[7] < 0.0f) voxelIndex |= 128;

        if (edgeTable[voxelIndex] == 0)
            return;

        if (edgeTable[voxelIndex] & 1)
        {
            vertexList[0] = vertexLinearInterp(voxel.cornerPositions[0], voxel.cornerPositions[1], voxel.cornerValue[0], voxel.cornerValue[1]);
        }
        if (edgeTable[voxelIndex] & 2)
        {
            vertexList[1] = vertexLinearInterp(voxel.cornerPositions[1], voxel.cornerPositions[2], voxel.cornerValue[1], voxel.cornerValue[2]);
        }
        if (edgeTable[voxelIndex] & 4)
        {
            vertexList[2] = vertexLinearInterp(voxel.cornerPositions[2], voxel.cornerPositions[3], voxel.cornerValue[2], voxel.cornerValue[3]);
        }
        if (edgeTable[voxelIndex] & 8)
        {
            vertexList[3] = vertexLinearInterp(voxel.cornerPositions[3], voxel.cornerPositions[4], voxel.cornerValue[3], voxel.cornerValue[4]);
        }
        if (edgeTable[voxelIndex] & 16)
        {
            vertexList[4] = vertexLinearInterp(voxel.cornerPositions[4], voxel.cornerPositions[4], voxel.cornerValue[4], voxel.cornerValue[5]);
        }
        if (edgeTable[voxelIndex] & 32)
        {
            vertexList[5] = vertexLinearInterp(voxel.cornerPositions[5], voxel.cornerPositions[6], voxel.cornerValue[5], voxel.cornerValue[6]);
        }
        if (edgeTable[voxelIndex] & 64)
        {
            vertexList[6] = vertexLinearInterp(voxel.cornerPositions[6], voxel.cornerPositions[7], voxel.cornerValue[6], voxel.cornerValue[7]);
        }
        if (edgeTable[voxelIndex] & 128)
        {
            vertexList[7] = vertexLinearInterp(voxel.cornerPositions[7], voxel.cornerPositions[4], voxel.cornerValue[7], voxel.cornerValue[4]);
        }
        if (edgeTable[voxelIndex] & 256)
        {
            vertexList[8] = vertexLinearInterp(voxel.cornerPositions[0], voxel.cornerPositions[4], voxel.cornerValue[0], voxel.cornerValue[4]);
        }
        if (edgeTable[voxelIndex] & 512)
        {
            vertexList[9] = vertexLinearInterp(voxel.cornerPositions[1], voxel.cornerPositions[5], voxel.cornerValue[1], voxel.cornerValue[5]);
        }
        if (edgeTable[voxelIndex] & 1024)
        {
            vertexList[10] = vertexLinearInterp(voxel.cornerPositions[2], voxel.cornerPositions[6], voxel.cornerValue[2], voxel.cornerValue[6]);
        }
        if (edgeTable[voxelIndex] & 2048)
        {
            vertexList[11] = vertexLinearInterp(voxel.cornerPositions[3], voxel.cornerPositions[7], voxel.cornerValue[3], voxel.cornerValue[7]);
        }
       
        /* Add triangle vertices to entire vertices vector */
        for (int i = 0; triangleTable[voxelIndex][i] != -1; i += 3) {
            vertices.push_back(vertexList[triangleTable[voxelIndex][i]]);
            vertices.push_back(vertexList[triangleTable[voxelIndex][i + 1]]);
            vertices.push_back(vertexList[triangleTable[voxelIndex][i + 2]]);
        }
        return;
    }

    Vector3 vertexLinearInterp(const Vector3 &p1, const Vector3 &p2, float valueP1, float valueP2)
    {
        return (p1 + (-valueP1 / (valueP2 - valueP1)) * (p2 - p1));
    }
}