#pragma once

#include <atlas/gl/GL.hpp>
#include <atlas/utils/GUI.hpp>
#include <atlas/tools/Tools.hpp>
#include <atlas/utils/Geometry.hpp>
#include <atlas/gl/VertexArrayObject.hpp>
#include <atlas/gl/Buffer.hpp>
#include <atlas/gl/ShaderUnit.hpp>
#include <vector>
#include <iostream>
#include <stack>
#include <math.h>
#include "TurtleValue.hpp"

namespace assignment3
{
    class PythagorasTree : public atlas::utils::Geometry
    {
        using Point = atlas::math::Point;
        using Stack = std::stack<TurtleValue>;
    public:

        PythagorasTree::PythagorasTree(std::string axiom);
        ~PythagorasTree() {};

        void renderGeometry() override;
        void recurse(std::string &system, int n);
        void generateLSystem(int recursionLevel, bool stochastic);

        const std::string& lSystem() const { return _lSystem; };
        std::string& lSystem() { return _lSystem; };

        const float &minAngle() const { return _minAngle; };
        float& minAngle() { return _minAngle; };

        const float &maxAngle() const { return _maxAngle; };
        float& maxAngle() { return _maxAngle; };

        void setAngleRange(float min, float max) { 
            _minAngle = min;
            _maxAngle = max;
        }
    private:
        std::string _lAxiom;
        std::string _lSystem;
        
        atlas::gl::VertexArrayObject _Vao;
        atlas::gl::Buffer _Buffer;
        std::size_t _NumIndices;

        std::vector<Point> _Vertices;

        //Stochastic values
        float _minAngle = -0.0f;
        float _maxAngle = 45.0f;
    };
}