#include "Polygonize.hpp"
#include "LookupTables.hpp"
#include "atlas/gl/Shader.hpp"
#include <vector>
#include <iostream>

namespace assignment2
{
    constexpr auto gridFS =
        R"(#version 430 core
uniform vec4 colour;
out vec4 fragColour;
void main()
{
    fragColour = colour;
}
)";

    using Vector3 = atlas::math::Vector;

    //Instantiate BSpline
    Polygonize::Polygonize() :
        mBuffer(GL_ARRAY_BUFFER)
    {
        std::vector<atlas::gl::ShaderUnit> shaders
        {
            { gridFS, GL_FRAGMENT_SHADER, true }
        };

        mShaders.push_back(atlas::gl::Shader(shaders));
        mShaders[0].compileShaders();
        mShaders[0].linkShaders();

        //BSplines
        /*mVao.bindVertexArray();
        mBuffer.bindBuffer();
        mBuffer.bufferData(atlas::gl::size<atlas::math::Vector>(BSplinePoints.size()),
            BSplinePoints.data(), GL_STREAM_DRAW);
        mBuffer.vertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0,
            atlas::gl::bufferOffset<float>(0));
        mVao.enableVertexAttribArray(0);

        auto var = mShaders[0].getUniformVariable("colour");
        mUniforms.insert(UniformKey("colour", var));

        mBuffer.unBindBuffer();
        mVao.unBindVertexArray();*/

        mShaders[0].disableShaders();
    }

    //Render the generated splines
    void Polygonize::renderGeometry()
    {
        if (!mShaders[0].shaderProgramValid())
        {
            return;
        }

        mShaders[0].enableShaders();
        mVao.bindVertexArray();

        float rgb = 0.0f;
        glUniform4f(mUniforms["colour"], 255.0f, rgb, rgb, 1);

        //glDrawArrays(GL_LINE_STRIP, 0, BSplinePoints.size());

        mVao.unBindVertexArray();
        mShaders[0].disableShaders();
    }
}