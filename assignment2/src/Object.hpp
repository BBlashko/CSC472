#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "Color.hpp"


namespace assignment2
{
    class Object : public atlas::utils::Geometry
    {
    public:
        Object() {};

        void Object::renderGeometry() override;

    private:
        atlas::gl::VertexArrayObject mVao;
        atlas::gl::Buffer mBuffer;
    };
}

#endif