#pragma once

#include "atlas/tools/ModellingScene.hpp"
#include "circle.h"
#include <GLFW\glfw3.h>
#include <atlas/utils/GUI.hpp>
#include <GL/GL.h>
#include <vector>
#include <iostream>

namespace assignment1
{
    class BSplineScene : public atlas::tools::ModellingScene
    {
    public:
        std::vector<assignment1::Circle> circlePoints;

        BSplineScene();

        void mousePressEvent(int button, int action, int modifiers,
            double xPos, double yPos) override;
        void updateScene(double time) override;
        void renderScene() override;

        void addCirclePoint(assignment1::Circle circle)
        {
            circlePoints.push_back(circle);
        };
    private:
       
    };
}