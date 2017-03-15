#include "LSystemScene.hpp"

namespace assignment3
{
    using  Vector3 = atlas::math::Vector;
    LSystemScene::LSystemScene() : _pTree("0"), _current_level(0)
    {}

    void LSystemScene::renderScene()
    {
        atlas::utils::Gui::getInstance().newFrame();
        const float grey = 161.0f / 255.0f;
        glClearColor(grey, grey, grey, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ImGui::SetNextWindowSize(ImVec2(400, 200), ImGuiSetCond_FirstUseEver);
        ImGui::Begin("LSystem - Pythagoras Tree");

        static int recursion = 0;
        static bool stochastic;
        static float minAngle = 0.0f;
        static float maxAngle = 45.0f;

        ImGui::Text("Axiom: 0");
        ImGui::Checkbox("Stochastic", &stochastic);
        if (stochastic)
        {
            ImGui::SliderFloat("Minimim Angle", &minAngle, 0.0f, 45.0f);
            ImGui::SliderFloat("Maximum Angle", &maxAngle, 0.0f, 45.0f);
            if (minAngle > maxAngle)
            {
                minAngle = maxAngle;
            }
            if (minAngle != _pTree.minAngle() || maxAngle != _pTree.maxAngle())
            {
                _pTree.setAngleRange(minAngle, maxAngle);
                _pTree.generateLSystem(_current_level, _current_stochastic);
            }
        }


        ImGui::InputInt("Level", &recursion);

        if (_current_level != recursion || _current_stochastic != stochastic)
        {
            _current_level = recursion;
            _current_stochastic = stochastic;
            _pTree.generateLSystem(_current_level, _current_stochastic);
        }
        ImGui::TextWrapped(_pTree.lSystem().c_str());

        _pTree.renderGeometry();

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f /
            ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        
        ImGui::End();
        ImGui::Render();
    }
}
