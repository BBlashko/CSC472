#include "PolygonizationScene.hpp"
#include "MarchingCubes.hpp"
#include "Sphere.hpp"
#include <vector>
#include <atlas/gl/GL.hpp>
#include <atlas/utils/GUI.hpp>

namespace assignment2
{
    using  Vector3 = atlas::math::Vector;

    PolygonizationScene::PolygonizationScene()
    {
        mSceneMesh.addSceneSphere(new Sphere(Vector3(-3.0f, 0, 0), 2.0f));
        mSceneMesh.addSceneSphere(new Sphere(2.2f));
        mSceneMesh.createMesh();
    }

    void PolygonizationScene::renderScene()
    {
        atlas::utils::Gui::getInstance().newFrame();
        const float grey = 161.0f / 255.0f;
        glClearColor(grey, grey, grey, 1.0f);
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

        if (mShowGrid)
        {
            mGrid.renderGeometry(mProjection, mView);
        }

        mSceneMesh.renderGeometry(mProjection, mView);

        ImGui::SetNextWindowSize(ImVec2(400, 200), ImGuiSetCond_FirstUseEver);
        ImGui::Begin("Polygonization HUD");
        ImGui::Checkbox("Show grid", &mShowGrid);
        if (ImGui::Button("Reset Camera"))
        {
            mCamera.resetCamera();
        }

        static int e = 0;
        ImGui::Text("Rendering Type:");
        ImGui::RadioButton("Atlas Mesh", &e, 0);
        ImGui::RadioButton("Lines", &e, 1);
        ImGui::RadioButton("Points", &e, 2);
        mSceneMesh.setRenderType(e);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f /
            ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();
        ImGui::Render();
    }
}