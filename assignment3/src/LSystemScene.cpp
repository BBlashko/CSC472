#include "LSystemScene.hpp"
#include "PythagorasTree.hpp"
#include <atlas/gl/GL.hpp>
#include <atlas/utils/GUI.hpp>

namespace assignment3
{
    using  Vector3 = atlas::math::Vector;
    LSystemScene::LSystemScene() : _pTree("0"), _current_level(0)
    {
        _pTree.generateLSystem(_current_level);
    }

    void LSystemScene::renderScene()
    {
        atlas::utils::Gui::getInstance().newFrame();
        const float grey = 161.0f / 255.0f;
        glClearColor(grey, grey, grey, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //mProjection = glm::perspective(
        //    glm::radians(mCamera.getCameraFOV()),
        //    (float)mWidth / mHeight, 1.0f, 1000000.0f);

        //mUniformMatrixBuffer.bindBuffer();
        //mUniformMatrixBuffer.bufferSubData(0, sizeof(atlas::math::Matrix4),
        //    &mProjection[0][0]);
        //mUniformMatrixBuffer.unBindBuffer();

        //mView = mCamera.getCameraMatrix();
        //mUniformMatrixBuffer.bindBuffer();
        //mUniformMatrixBuffer.bufferSubData(sizeof(atlas::math::Matrix4),
        //    sizeof(atlas::math::Matrix4), &mView[0][0]);

        ImGui::SetNextWindowSize(ImVec2(400, 200), ImGuiSetCond_FirstUseEver);
        ImGui::Begin("L-System HUD");

        static int recursion = 0;
        ImGui::Text("Axiom: 0");
        ImGui::InputInt("Level", &recursion);
        if (_current_level != recursion)
        {
            _current_level = recursion;
            _pTree.generateLSystem(recursion);
        }
        ImGui::TextWrapped(_pTree.lSystem().c_str());

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f /
            ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();
        ImGui::Render();
    }
}
