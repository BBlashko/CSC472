#include "Sphere.hpp"

namespace assignment2
{
    Sphere::Sphere(Vector3 position, float radius) : 
        mRadius(radius),
        mPosition(position)
    { }

    float Sphere::function()
    {
        return mPosition.x * mPosition.x + mPosition.y * mPosition.y + mPosition.z * mPosition.z - mRadius * mRadius;
    }
    void Sphere::renderGeometry()
    {
    }
}
