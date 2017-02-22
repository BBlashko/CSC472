#include "Mesh.hpp"

namespace assignment2
{
    constexpr auto gridVs =
        R"(#version 430 core

layout (location = 0) in vec3 vPosition;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
    gl_Position = projection * view * model * vec4(vPosition, 1.0);
}
)";

    constexpr auto gridFS =
        R"(#version 430 core

uniform vec4 colour;

out vec4 fragColour;

void main()
{
    fragColour = colour;
}
)";

    Mesh::Mesh() : 
        mBuffer(GL_ARRAY_BUFFER)
    {
        currentRenderType = ATLAS_MESH;
    }

    void Mesh::addSceneSphere(Sphere *sphere)
    {
        mMeshSpheres.push_back(sphere);
    }

    void Mesh::createMesh()
    {
        if (mMeshSpheres.size() == 0)
        {
            std::cerr << "Cannot create a mesh with no spheres" << std::endl;
            return;
        }
        marchingCubes.createMesh(mMeshSpheres, mMeshVertices, mMeshNormals);
        mNumIndices = mMeshVertices.size();
        std::cout << "Size = " << mMeshNormals.size() << std::endl;
        std::cout << "Size = " << mMeshVertices.size() << std::endl;

        std::vector<GLuint> indices(mNumIndices);
        std::iota(std::begin(indices), std::end(indices), 0);
        
        AtlasMesh::fromTriangleSoup(this->mMeshVertices, indices, this->mAtlasMesh, this->mMeshNormals);

      

        mModel = atlas::math::Matrix4(1.0f);

        std::vector<atlas::gl::ShaderUnit> shaders
        {
            { gridVs, GL_VERTEX_SHADER, true },
            { gridFS, GL_FRAGMENT_SHADER, true }
        };

        mShaders.push_back(atlas::gl::Shader(shaders));
        mShaders[0].compileShaders();
        mShaders[0].linkShaders();


        mVao.bindVertexArray();
        mBuffer.bindBuffer();
        mBuffer.bufferData(atlas::gl::size<atlas::math::Vector>(mNumIndices),
            mMeshVertices.data(), GL_STATIC_DRAW);
        mBuffer.vertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0,
            atlas::gl::bufferOffset<float>(0));
        mVao.enableVertexAttribArray(0);

        auto var = mShaders[0].getUniformVariable("projection");
        mUniforms.insert(UniformKey("projection", var));

        var = mShaders[0].getUniformVariable("view");
        mUniforms.insert(UniformKey("view", var));

        var = mShaders[0].getUniformVariable("model");
        mUniforms.insert(UniformKey("model", var));

        var = mShaders[0].getUniformVariable("colour");
        mUniforms.insert(UniformKey("colour", var));

        mBuffer.unBindBuffer();
        mVao.unBindVertexArray();
        mShaders[0].disableShaders();
    }

    void Mesh::setRenderType(int type)
    {
        if (type == 0)
        {
            currentRenderType = ATLAS_MESH;
        }
        else if (type == 1)
        {
            currentRenderType = LINES;
        }
        else if (type == 2)
        {
            currentRenderType = VERTICES;
        }
    }

    void Mesh::renderGeometry(atlas::math::Matrix4 const & projection, atlas::math::Matrix4 const & view)
    {
        if (!mShaders[0].shaderProgramValid() || mMeshVertices.size() == 0)
        {
            return;
        }

        mShaders[0].enableShaders();
        mVao.bindVertexArray();

        glUniformMatrix4fv(mUniforms["projection"], 1, GL_FALSE, &projection[0][0]);
        glUniformMatrix4fv(mUniforms["view"], 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(mUniforms["model"], 1, GL_FALSE, &mModel[0][0]);

        switch (currentRenderType)
        {
            case ATLAS_MESH:
                glUniform4f(mUniforms["colour"], 0.4, 0.1, 0.4, 0.7);
                mAtlasMesh.setVertexAttribArrays({ 0, 1 });
                mAtlasMesh.renderMesh();
                break;
            case LINES:
                glUniform4f(mUniforms["colour"], 0, 0.7, 0, 1);
                glDrawArrays(GL_LINES, 0, (int)mNumIndices);
                break;
            case VERTICES:
                glUniform4f(mUniforms["colour"], 1, 0, 0, 1);
                glPointSize(4.0f);
                glDrawArrays(GL_POINTS, 0, (int)mNumIndices);
                break;
        }

        mVao.unBindVertexArray();
        mShaders[0].disableShaders();
    }

}
