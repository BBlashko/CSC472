#pragma once
#include "MarchingCubes.hpp"
#include "LookupTables.hpp"
#include "atlas\utils\Utils.hpp"
#include "atlas/math/Math.hpp"
#include <math.h>
#include <iostream>

namespace assignment2
{
    void MarchingCubes::createMesh(std::vector<Sphere*>& SceneSpheres, std::vector<Normal> &vertices, std::vector<Normal> &normals )
    {
        mSceneSpheres = SceneSpheres;

        //Create the grid that contains the objects
        if (generateGrid() == 1)
        {
            printf("Failed to generate a grid for the spheres in the scene");
        };

        float *vertexValueGrid1 = new float[mSceneGrid.xSize * mSceneGrid.zSize];
        float *vertexValueGrid2 = new float[mSceneGrid.xSize * mSceneGrid.zSize];

        std::cout << "Size of Grid = " << mSceneGrid.xSize * mSceneGrid.zSize << std::endl;
        calculateVertexValues(vertexValueGrid1, 0);
        
        for (int y = 1; y < mSceneGrid.ySize; y++)
        {
            if (y % 2 == 1)
            {
                calculateVertexValues(vertexValueGrid2, y);
                calculateVoxels(vertexValueGrid1, vertexValueGrid2, y-1, vertices, normals);
            }
            else
            {
                calculateVertexValues(vertexValueGrid1, y);
                calculateVoxels(vertexValueGrid2, vertexValueGrid1, y-1, vertices, normals);
            }
        }
        delete[] vertexValueGrid1;
        delete[] vertexValueGrid2;      

    }

    void MarchingCubes::calculateVertexValues(float *vertexArray, int y)
    {
        for (int x = 0; x < mSceneGrid.xSize; x++)
        {
            for (int z = 0; z < mSceneGrid.zSize; z++)
            {
                Vector3 position = Vector3(mSceneGrid.boundingBox[0].x + (x * VOXEL_SIZE),
                                           mSceneGrid.boundingBox[0].y + (y * VOXEL_SIZE),
                                           mSceneGrid.boundingBox[0].z + (z * VOXEL_SIZE));
               

                float value = 1;
                for (int i = 0; i < mSceneSpheres.size(); i++)
                {

                    value = mSceneSpheres.at(i)->contains(position);
                    if (value == 0)
                    {
                        break;
                    }
                }
                vertexArray[x * mSceneGrid.zSize + z] = value;
            }
        }
    }

    void MarchingCubes::calculateVoxels(float * bottomVertexArray, float *topVertexArray, int y, std::vector<Vector3> &vertices, std::vector<Normal> &normals)
    {
        
        for (int x = 0; x < mSceneGrid.xSize - 1; x++)
        {
            for (int z = 0; z < mSceneGrid.zSize - 1; z++)
            {
                Voxel voxel;
                //back side positions
                voxel.cornerPositions[0] = Vector3(mSceneGrid.boundingBox[0].x + (x * VOXEL_SIZE), mSceneGrid.boundingBox[0].y + (y * VOXEL_SIZE), mSceneGrid.boundingBox[0].b + (z * VOXEL_SIZE));
                voxel.cornerPositions[1] = Vector3(mSceneGrid.boundingBox[0].x + ((x + 1) * VOXEL_SIZE), mSceneGrid.boundingBox[0].y + (y * VOXEL_SIZE), mSceneGrid.boundingBox[0].z + (z * VOXEL_SIZE));
                voxel.cornerPositions[2] = Vector3(mSceneGrid.boundingBox[0].x + ((x + 1) * VOXEL_SIZE), mSceneGrid.boundingBox[0].y + (y * VOXEL_SIZE), mSceneGrid.boundingBox[0].z + ((z + 1) * VOXEL_SIZE));
                voxel.cornerPositions[3] = Vector3(mSceneGrid.boundingBox[0].x + (x * VOXEL_SIZE), mSceneGrid.boundingBox[0].y + (y * VOXEL_SIZE), mSceneGrid.boundingBox[0].z + ((z + 1) * VOXEL_SIZE));

                //front side positions
                voxel.cornerPositions[4] = Vector3(mSceneGrid.boundingBox[0].x + (x * VOXEL_SIZE), mSceneGrid.boundingBox[0].y + ((y + 1) * VOXEL_SIZE), mSceneGrid.boundingBox[0].z + (z * VOXEL_SIZE));
                voxel.cornerPositions[5] = Vector3(mSceneGrid.boundingBox[0].x + ((x + 1) * VOXEL_SIZE), mSceneGrid.boundingBox[0].y + ((y + 1) * VOXEL_SIZE), mSceneGrid.boundingBox[0].z + (z * VOXEL_SIZE));
                voxel.cornerPositions[6] = Vector3(mSceneGrid.boundingBox[0].x + ((x + 1) * VOXEL_SIZE), mSceneGrid.boundingBox[0].y + ((y + 1) * VOXEL_SIZE), mSceneGrid.boundingBox[0].z + ((z + 1) * VOXEL_SIZE));
                voxel.cornerPositions[7] = Vector3(mSceneGrid.boundingBox[0].x + (x * VOXEL_SIZE), mSceneGrid.boundingBox[0].y + ((y + 1) * VOXEL_SIZE), mSceneGrid.boundingBox[0].z + ((z + 1) * VOXEL_SIZE));

                //back side values
                voxel.cornerValue[0] = bottomVertexArray[x * mSceneGrid.zSize + z];
                voxel.cornerValue[1] = bottomVertexArray[(x + 1) * mSceneGrid.zSize + z];
                voxel.cornerValue[2] = bottomVertexArray[(x + 1) * mSceneGrid.zSize + (z + 1)];
                voxel.cornerValue[3] = bottomVertexArray[x * mSceneGrid.zSize + (z + 1)];
                
                //front side values
                voxel.cornerValue[4] = topVertexArray[x * mSceneGrid.zSize + z];
                voxel.cornerValue[5] = topVertexArray[(x + 1) * mSceneGrid.zSize + z ];
                voxel.cornerValue[6] = topVertexArray[(x + 1) * mSceneGrid.zSize + (z + 1)];
                voxel.cornerValue[7] = topVertexArray[x * mSceneGrid.zSize + (z + 1)];

                polygonizeVoxel(voxel, vertices, normals, ISO_VALUE);
                
            }
        }
    }

    int MarchingCubes::generateGrid()
    {
        if (mSceneSpheres.size() == 0)
        {
            return 1;
        }
        //Create BoundingBox
        Sphere *sphere = mSceneSpheres.at(0);
        int minX = (int)floor(sphere->x() - sphere->radius());
        int minY = (int)floor(sphere->y() - sphere->radius());
        int minZ = (int)floor(sphere->z() - sphere->radius());
        int maxX = (int)ceil(sphere->x() + sphere->radius());
        int maxY = (int)ceil(sphere->y() + sphere->radius());
        int maxZ = (int)ceil(sphere->z() + sphere->radius());

        
    
        int temp;
        for (int i = 1; i < mSceneSpheres.size(); i++)
        {
            sphere = mSceneSpheres.at(i);
            if ((temp = (int)floor(sphere->x() - sphere->radius())) < minX) minX = temp;
            if ((temp = (int)floor(sphere->y() - sphere->radius())) < minY) minY = temp;
            if ((temp = (int)floor(sphere->z() - sphere->radius())) < minZ) minZ = temp;
            if ((temp = (int)ceil(sphere->x() + sphere->radius())) > maxX) maxX = temp;
            if ((temp = (int)ceil(sphere->y() + sphere->radius())) > maxY) maxY = temp;
            if ((temp = (int)ceil(sphere->z() + sphere->radius())) > maxZ) maxZ = temp;
        }

        mSceneGrid.boundingBox[0] = Vector3(minX, minY, minZ);
        mSceneGrid.boundingBox[1] = Vector3(maxX, minY, minZ);
        mSceneGrid.boundingBox[2] = Vector3(minX, maxY, minZ);
        mSceneGrid.boundingBox[3] = Vector3(maxX, maxY, minZ);
        mSceneGrid.boundingBox[4] = Vector3(minX, minY, maxZ);
        mSceneGrid.boundingBox[5] = Vector3(maxX, minY, maxZ);
        mSceneGrid.boundingBox[6] = Vector3(minX, maxY, maxZ);
        mSceneGrid.boundingBox[7] = Vector3(maxX, maxY, maxZ);
        
        mSceneGrid.xSize = (int) ((maxX - minX) / VOXEL_SIZE) + 1;
        mSceneGrid.ySize = (int) ((maxY - minY) / VOXEL_SIZE) + 1;
        mSceneGrid.zSize = (int) ((maxZ - minZ) / VOXEL_SIZE) + 1;

        return 0;
    }

    void MarchingCubes::polygonizeVoxel(Voxel voxel, std::vector<Vector3> &vertices, std::vector<Normal> &normals, float isoLevel)
    {
        Vector3 vertexList[12];

        int voxelIndex = 0;
        if (voxel.cornerValue[0] < isoLevel) voxelIndex |= 1;
        if (voxel.cornerValue[1] < isoLevel) voxelIndex |= 2;
        if (voxel.cornerValue[2] < isoLevel) voxelIndex |= 4;
        if (voxel.cornerValue[3] < isoLevel) voxelIndex |= 8;
        if (voxel.cornerValue[4] < isoLevel) voxelIndex |= 16;
        if (voxel.cornerValue[5] < isoLevel) voxelIndex |= 32;
        if (voxel.cornerValue[6] < isoLevel) voxelIndex |= 64;
        if (voxel.cornerValue[7] < isoLevel) voxelIndex |= 128;

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
            vertexList[3] = vertexLinearInterp(voxel.cornerPositions[3], voxel.cornerPositions[0], voxel.cornerValue[3], voxel.cornerValue[0]);
        }
        if (edgeTable[voxelIndex] & 16)
        {
            vertexList[4] = vertexLinearInterp(voxel.cornerPositions[4], voxel.cornerPositions[5], voxel.cornerValue[4], voxel.cornerValue[5]);
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
            Vector3 vec1 = vertexList[triangleTable[voxelIndex][i]];
            Vector3 vec2 = vertexList[triangleTable[voxelIndex][i + 1]];
            Vector3 vec3 = vertexList[triangleTable[voxelIndex][i + 1]];

            Normal norm = glm::normalize(glm::cross(vec2 - vec1, vec3 - vec1));

            normals.push_back(norm);
            normals.push_back(norm);
            normals.push_back(norm);

            vertices.push_back(vertexList[triangleTable[voxelIndex][i]]);
            vertices.push_back(vertexList[triangleTable[voxelIndex][i + 1]]);
            vertices.push_back(vertexList[triangleTable[voxelIndex][i + 2]]);
        }

        return;
    }

    Vector3 MarchingCubes::vertexLinearInterp(const Vector3 & p1, const Vector3 & p2, float valueP1, float valueP2)
    {
        return (p1 + (-valueP1 / (valueP2 - valueP1)) * (p2 - p1));
    }
}