#pragma once
/**
*	\file Grid.hpp
*	\brief Defines a simple grid used for reference when modeling.
*/

#pragma once

#include "atlas/tools/Tools.hpp"
#include "atlas/utils/Geometry.hpp"
#include "atlas/gl/VertexArrayObject.hpp"
#include "atlas/gl/Buffer.hpp"

namespace assignment1
{
    class Circle final : public atlas::utils::Geometry
    {
    public:
        Circle::Circle(double xPos = 0, double yPos = 0, double radius = 120, int numberOfSides = 36);
        void renderGeometry() override;

    private:
        atlas::gl::VertexArrayObject mVao;
        atlas::gl::Buffer mBuffer;
        double xPos, yPos, radius;

        int numberOfVertices, numberOfSides;
        GLfloat* allCircleVertices;
        
    };
}