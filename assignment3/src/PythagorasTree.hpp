#pragma once

#include "atlas/tools/Tools.hpp"
#include "atlas/utils/Geometry.hpp"
#include "atlas/gl/VertexArrayObject.hpp"
#include "atlas/gl/Buffer.hpp"
#include <vector>

namespace assignment3
{
    class PythagorasTree : public atlas::utils::Geometry
    {
    public:
        PythagorasTree::PythagorasTree(std::string axiom) : _lAxiom(axiom) {};
        ~PythagorasTree() {};

        void renderGeometry() override;
        void recurse(std::string &system, int n);
        std::string generateLSystem(int recursionLevel);
        //generate rules

    private:
        std::string _lAxiom;
        std::string _lSystem;
    };
}