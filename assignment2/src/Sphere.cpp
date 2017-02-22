#include "Sphere.hpp"
#include <iostream>

namespace assignment2
{
    float Sphere::contains(Vector3 vertex)
    {
        float distance = glm::distance(vertex, mPosition);

        if (distance <= mRadius)
        {
            return 0;
        }
        return 1;
    }

    void Sphere::renderGeometry()
    {
    }
}
