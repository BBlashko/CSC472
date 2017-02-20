#pragma once
#include "Object.hpp"

namespace assignment2
{
    class Sphere : public Object
    {
        public:
            Sphere::Sphere(float radius);
            void Sphere::function();

        private:
            float mRadius;

    };

}