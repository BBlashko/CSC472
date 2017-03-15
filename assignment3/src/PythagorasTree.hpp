#pragma once

#include "atlas/tools/Tools.hpp"
#include "atlas/utils/Geometry.hpp"
#include "atlas/gl/VertexArrayObject.hpp"
#include "atlas/gl/Buffer.hpp"
#include <vector>
#include <stack>

namespace assignment3
{
    class PythagorasTree : public atlas::utils::Geometry
    {
        using Point = atlas::math::Point;
        using Stack = std::stack<Point, int>;
    public:

        PythagorasTree::PythagorasTree(std::string axiom);
        ~PythagorasTree() {};

        void renderGeometry() override;
        void recurse(std::string &system, int n);
        void generateLSystem(int recursionLevel);

        const std::string& lSystem() const { return _lSystem; };
        std::string& lSystem() { return _lSystem; };
    private:
        std::string _lAxiom;
        std::string _lSystem;
        
        atlas::gl::VertexArrayObject _Vao;
        atlas::gl::Buffer _Buffer;
        std::size_t _NumIndices;

        std::vector<Point> _Vertices;
    };
}