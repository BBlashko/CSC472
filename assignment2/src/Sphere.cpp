#include "Sphere.hpp"

namespace assignment2
{
    /*float Sphere::function()
    {
        return mPosition.x * mPosition.x + mPosition.y * mPosition.y + mPosition.z * mPosition.z - mRadius * mRadius;
    }*/

    /*void Sphere::isoLevel(Vector3)*/

    int Sphere::contains(Vector3 vertex)
    {
        float distance = glm::distance(vertex, mPosition);

        if (distance < mRadius)
        {
            return 0;
        }
        return 1;
    }

    void Sphere::renderGeometry()
    {
    }
}
