#pragma once
#include <atlas/tools/ModellingScene.hpp>
#include <atlas/utils/GUI.hpp>
#include <atlas/gl/GL.hpp>
#include <atlas/utils/GUI.hpp>
#include <GLFW\glfw3.h>
#include <GL/GL.h>
#include <vector>
#include <iostream>
#include "PythagorasTree.hpp"

namespace assignment3
{
    class LSystemScene : public atlas::tools::ModellingScene
    {
    public:
        LSystemScene::LSystemScene();
        void LSystemScene::renderScene() override;
    private:
        PythagorasTree _pTree;
        int _current_level;
        bool _current_stochastic;
    };
}
