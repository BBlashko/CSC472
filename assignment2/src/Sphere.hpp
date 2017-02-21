#pragma once
//#include "Object.hpp"
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
            Sphere::Sphere() :
                mPosition(Vector3(0,0,0)),
                mRadius(1.0f){};

            Sphere::Sphere(Vector3 position) :
                mPosition(position),
                mRadius(1.0f) {};

            Sphere::Sphere(float radius) :
                mPosition(Vector3(0,0,0)),
                mRadius(radius) {};

            Sphere::Sphere(Vector3 position, float radius) :
                mPosition(position),
                mRadius(radius) {};

            ~Sphere() {};

            int Sphere::contains(Vector3 vertex);
            void renderGeometry() override;

            const float& x() const { return mPosition.x; };
            float& x() { return mPosition.x; };

            const float& y() const { return mPosition.y; };
            float& y() { return mPosition.y; };

            const float& z() const { return mPosition.z; };
            float& z() { return mPosition.z; };

            const float& radius() const { return mRadius; };
            float& radius() { return mRadius; };

        private:
            float mRadius;
            Vector3 mPosition;

    };

}