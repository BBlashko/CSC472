#pragma once

#include "PythagorasTree.hpp"
#include "atlas/tools/ModellingScene.hpp"
#include <GLFW\glfw3.h>
#include <atlas/utils/GUI.hpp>
#include <GL/GL.h>
#include <vector>
#include <iostream>

namespace assignment3
{
    class LSystemScene : public atlas::tools::ModellingScene
    {
    public:
        LSystemScene();
        void renderScene() override;
    private:
        PythagorasTree _pTree;
    };
}
