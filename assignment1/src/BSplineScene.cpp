#include "BSplineScene.h"

namespace assignment1
{
    BSplineScene::BSplineScene()
    {

    }

    void BSplineScene::mousePressEvent(int button, int action, int modifiers, double xPos, double yPos)
    {
        atlas::utils::Gui::getInstance().mousePressed(button, action, modifiers);

        if (action == GLFW_PRESS)
        {
            atlas::math::Point2 point(xPos, yPos);
            addCirclePoint(assignment1::Circle(xPos, yPos, 120, 36));
        }
        else
        {
            mCamera.mouseUp();
        }
    }

    void BSplineScene::updateScene(double time)
    {

    }

    void BSplineScene::renderScene()
    {
        static int begin_i = 0, end_i = 10;

        atlas::utils::Gui::getInstance().newFrame();

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        mProjection = glm::perspective(
            glm::radians(mCamera.getCameraFOV()),
            (float)mWidth / mHeight, 1.0f, 1000000.0f);

        mUniformMatrixBuffer.bindBuffer();
        mUniformMatrixBuffer.bufferSubData(0, sizeof(atlas::math::Matrix4),
            &mProjection[0][0]);
        mUniformMatrixBuffer.unBindBuffer();

        mView = mCamera.getCameraMatrix();
        mUniformMatrixBuffer.bindBuffer();
        mUniformMatrixBuffer.bufferSubData(sizeof(atlas::math::Matrix4),
            sizeof(atlas::math::Matrix4), &mView[0][0]);

        static char degreeChar[1] = { '0' };

        //Draw Circles
        for (std::vector<assignment1::Circle>::size_type i = 0; i != circlePoints.size(); i++) {
            assignment1::Circle &circle = circlePoints.at(i);
            circle.renderGeometry();
        }

        //static char degreeChar[1] = { '0' };
        //ImGui::InputText("Order", degreeChar, 1);

        ImGui::SetNextWindowSize(ImVec2(400, 200), ImGuiSetCond_FirstUseEver);
        ImGui::Begin("BSpline HUD");

        static int vec4i[4] = { 1, 10 };
        ImGui::SliderInt("Degree", vec4i, 1, 10);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f /
            ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();
        ImGui::Render();
    }
}