#pragma once
#include "Object.hpp"
#include "atlas/utils/Geometry.hpp"
#include "atlas/gl/VertexArrayObject.hpp"
#include "atlas/gl/Buffer.hpp"
#include "atlas/math/Math.hpp"

namespace assignment2
{
    class Sphere : public atlas::utils::Geometry
    {
        using Vector3 = atlas::math::Vector;

        public:
            Sphere::Sphere(Vector3 position, float radius);

            float Sphere::function();
            void renderGeometry() override;

        private:
            float mRadius;
            Vector3 mPosition;

    };

}