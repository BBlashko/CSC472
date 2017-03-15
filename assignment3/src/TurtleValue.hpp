#pragma once

#include "atlas/tools/Tools.hpp"
#include "atlas/utils/Geometry.hpp"
#include "atlas/gl/VertexArrayObject.hpp"
#include "atlas/gl/Buffer.hpp"
#include <vector>
#include <stack>

namespace assignment3
{
    class TurtleValue : public atlas::utils::Geometry
    {
        using Point = atlas::math::Point;
    public:
        TurtleValue(Point position, float angle) : _position(position), _angle(angle) {};
        // The copy constructor.
        TurtleValue(const TurtleValue& v)
        {
            _position = v._position;
            _angle = v._angle;
        };

        // The move constructor
        TurtleValue(TurtleValue&& v)
        {
            _position = v._position;
            _angle = v._angle;
        };

        // Destroy a vector.
        ~TurtleValue() {};

        // The copy assignment operator.
        TurtleValue& operator=(const TurtleValue v)
        {
            if (this != &v)
            {
                _position = v._position;
                _angle = v._angle;
            }
            return *this;
        };

        const Point& position() const { return _position; };
        Point& position() { return _position; };

        const float& angle() const { return _angle; };
        float& angle() { return _angle; };
    private:
        Point _position;
        float _angle;
    };
}