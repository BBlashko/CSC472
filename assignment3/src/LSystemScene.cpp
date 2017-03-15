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

        ImGui::SetNextWindowSize(ImVec2(400, 450), ImGuiSetCond_FirstUseEver);
        ImGui::Begin("LSystem - Pythagoras Tree");

        static int recursion = 0;
        static bool stochastic;
        static bool randomBranch;
        static float minAngle = 0.0f;
        static float maxAngle = 90.0f;
        static float minBranchLength = 0.0f;
        static float maxBranchLength = 0.05f;
        static float minLeafLength = 0.0f;
        static float maxLeafLength = 0.025f;

        ImGui::Text("Axiom: 0");
        ImGui::Checkbox("Stochastic", &stochastic);
        if (stochastic)
        {
            
            ImGui::Checkbox("Randomize Branches", &randomBranch);
            _pTree.setRandomizeLanguage(randomBranch);

            ImGui::Text("Randomize Branch Lengths:");
            ImGui::SliderFloat("Minimum Branch Length", &minBranchLength, 0.0f, 0.05f);
            ImGui::SliderFloat("Maximum Branch Length", &maxBranchLength, 0.0f, 0.05f);
            if (minBranchLength > maxBranchLength)
            {
                minBranchLength = maxBranchLength;
            }
            _pTree.setBranchRange(minBranchLength, maxBranchLength);

            ImGui::Text("Randomize  Leaf Lengths:");
            ImGui::SliderFloat("Minimum Leaf Length", &minLeafLength, 0.0f, 0.025f);
            ImGui::SliderFloat("Maximum Leaf Length", &maxLeafLength, 0.0f, 0.025f);
            if (minLeafLength > maxLeafLength)
            {
                minLeafLength = maxLeafLength;
            }
            _pTree.setLeafRange(minLeafLength, maxLeafLength);

            ImGui::Text("Randomize Angles:");
            ImGui::SliderFloat("Minimim Angle", &minAngle, 0.0f, 90.0f);
            ImGui::SliderFloat("Maximum Angle", &maxAngle, 0.0f, 90.0f);
            if (minAngle > maxAngle)
            {
                minAngle = maxAngle;
            }
            _pTree.setAngleRange(minAngle, maxAngle);
        }


        ImGui::InputInt("Recursion Level", &recursion);

        if (_current_level != recursion || _current_stochastic != stochastic)
        {
            _current_level = recursion;
            _current_stochastic = stochastic;
            _pTree.generateLSystem(_current_level, _current_stochastic);
        }

        if (ImGui::Button("Regenerate!"))
        {
            _pTree.generateLSystem(_current_level, _current_stochastic);
        }
        ImGui::Text("LSystem Language:");
        ImGui::TextWrapped(_pTree.lSystem().c_str());

        _pTree.renderGeometry();

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f /
            ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        
        ImGui::End();
        ImGui::Render();
    }
}
