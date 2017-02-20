#pragma once
#include "atlas/tools/ModellingScene.hpp"
#include "atlas/tools/Grid.hpp"
#include <GLFW\glfw3.h>
#include <atlas/utils/GUI.hpp>
#include <GL/GL.h>
#include <vector>
#include <iostream>

namespace assignment2
{
    class PolygonizationScene : public atlas::tools::ModellingScene
    {
        using Vector3 = atlas::math::Vector;

    public:
        PolygonizationScene::PolygonizationScene();

        void PolygonizationScene::renderScene() override;

    private:
    };
}