#pragma once
#include "Object.hpp"
#include "atlas/utils/Geometry.hpp"
#include "atlas/gl/VertexArrayObject.hpp"
#include "atlas/gl/Buffer.hpp"
#include <vector>

namespace assignment2
{
    class Polygonize : public atlas::utils::Geometry
    {

    public:
        Polygonize::Polygonize();

        void Polygonize::renderGeometry() override;

    private:
        atlas::gl::VertexArrayObject mVao;
        atlas::gl::Buffer mBuffer;
    };
}