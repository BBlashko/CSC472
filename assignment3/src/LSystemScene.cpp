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
        ImGui::Text("Axiom: 0");
        ImGui::InputInt("Level", &recursion);
        if (_current_level != recursion)
        {
            _current_level = recursion;
            _pTree.generateLSystem(recursion);
        }
        ImGui::TextWrapped(_pTree.lSystem().c_str());

        _pTree.renderGeometry();

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f /
            ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        
        ImGui::End();
        ImGui::Render();
    }
}
