#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "Color.hpp"


namespace assignment2
{
    struct RayResult
    {
        double t;
        //Vector3 normal;
        Color color;
    };

    class Object
    {
    public:
        Object() {};

        virtual void function() const = 0;
    };
}

#endif