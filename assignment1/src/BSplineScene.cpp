#include "BSplineScene.h"
#include <atlas\utils\Application.hpp>

namespace assignment1
{
    BSplineScene::BSplineScene()
    {
    }

    void BSplineScene::mousePressEvent(int button, int action, int modifiers, double xPos, double yPos)
    {
        atlas::utils::Gui::getInstance().mousePressed(button, action, modifiers);
        if (action == GLFW_PRESS && !ImGui::IsAnyItemHovered())
        {
            if (bSpline.intersectsControlPoint(xPos, yPos, 0.1))
            {
                while (action == GLFW_PRESS)
                {
                    
                }
            }
            else
            {
                double currWidth = (double)(mWidth / 2);
                double currHeight = (double)(mHeight / 2);
                bSpline.addControlPoint((xPos - currWidth) / currWidth, -((yPos - currHeight) / currHeight));
            }
        }
        else
        {
            mCamera.mouseUp();
        }
    }

    void BSplineScene::renderScene()
    {
        static int begin_i = 0, end_i = 10;

        atlas::utils::Gui::getInstance().newFrame();

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        static char degreeChar[1] = { '0' };

        //RenderBSplines
        bSpline.renderGeometry();

        ImGui::SetNextWindowSize(ImVec2(400, 200), ImGuiSetCond_FirstUseEver);
        ImGui::Begin("BSpline HUD");
        static int order = bSpline.getDegree() + 1;
        static int numPoints = 0;

        int currNum = bSpline.getNumberOfControlPoints();

        //GUI Order option
        ImGui::InputInt("Order:", &order);
        if (order != bSpline.getDegree() + 1)
        {
            if (order > 6)
            {
                order = 6;
            }
            else if (order < 1)
            {
                order = 1;
            }
            else
            {
                bSpline.setOrderAndDegree(order - 1);
                bSpline.updateSpline();
            }

        }

        //GUI Number of Control Points Option
        int currPoint = bSpline.getNumberOfControlPoints();
        if (numPoints != currPoint)
        {
            numPoints = currPoint;
        }
        ImGui::InputInt("Number of Control Points:", &numPoints);
        if (numPoints < 0)
        {
            numPoints = 0;
        }
        else if (currNum > numPoints)
        {
            numPoints -= 1;
            bSpline.removeControlPoint();
        }
        
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f /
            ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();
        ImGui::Render();
    }
}