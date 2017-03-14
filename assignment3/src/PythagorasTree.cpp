#include "PythagorasTree.hpp"
#include <atlas/gl/GL.hpp>
#include <atlas/utils/GUI.hpp>
#include <iostream>

namespace assignment3
{
    void PythagorasTree::renderGeometry()
    {
    }

    void PythagorasTree::recurse(std::string &system, int n)
    {
        if (n == 0)
        {
            return;
        }

        std::cout << "Hit 1" << std::endl;
        int size = system.length();
        for (int i = 0; i < system.length(); i++)
        {
            std::cout << "Hit 2" << std::endl;
            char c = system.at(i);

            if (c == '0')
            {
                std::cout << "Hit 3" << std::endl;
                system.erase(i, 1);
                system.insert(i, "1[0]0");
                i += 5;
            }
            else if (c == '1')
            {
                std::cout << "Hit 4" << std::endl;
                system.erase(i, 1);
                system.insert(i, "11");
                i += 1;
            }
        }
        std::cout << "Hit 5" << std::endl;
        recurse(system, n - 1);
    }

    std::string PythagorasTree::generateLSystem(int recursionLevel)
    {
        std::string system = _lAxiom;
        recurse(system, recursionLevel);
        return system;
    }
}