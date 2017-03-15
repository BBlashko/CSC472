#include "circle.h"
#include "atlas/gl/Shader.hpp"
#include "atlas\math\Math.hpp"

namespace assignment1
{
        constexpr auto gridVs =
            R"(#version 430 core

            layout (location = 0) in vec3 vPosition;

            layout (std140, binding = 0) uniform Matrices
{
    mat4 projection;
    mat4 view;
};

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

        Circle::Circle(double xPos, double yPos, double radius, const int numberOfSides) :
            mBuffer(GL_ARRAY_BUFFER),
            xPos(xPos),
            yPos(yPos),
            radius(radius),
            numberOfSides(numberOfSides),
            numberOfVertices(numberOfSides + 1)
    {
        GLfloat doublePi = 2.0f * 3.14f;

        GLfloat* circleVerticesX = new GLfloat[numberOfVertices];
        GLfloat* circleVerticesY = new GLfloat[numberOfVertices];
        GLfloat* circleVerticesZ = new GLfloat[numberOfVertices];

        printf("Circle 1\n");

        for (int i = 0; i < numberOfVertices; i++)
        {
            circleVerticesX[i] = xPos + (radius * cos(i * doublePi / numberOfSides));
            circleVerticesY[i] = yPos + (radius * sin(i * doublePi / numberOfSides));
            circleVerticesZ[i] = 0.0f;
        }

        printf("Circle 2\n");
        allCircleVertices = new GLfloat[numberOfVertices * 3];
        for (int i = 0; i < numberOfVertices; i++)
        {
            allCircleVertices[i * 3] = circleVerticesX[i];
            allCircleVertices[(i * 3) + 1] = circleVerticesY[i];
            allCircleVertices[(i * 3) + 2] = circleVerticesZ[i];
        }

        printf("Circle 3\n");
        mModel = atlas::math::Matrix4(1.0f);

        std::vector<atlas::gl::ShaderUnit> shaders
        {
            { gridVs, GL_VERTEX_SHADER, true },
            { gridFS, GL_FRAGMENT_SHADER, true }
        };

        printf("Circle 4\n");
        mShaders.push_back(atlas::gl::Shader(shaders));
        mShaders[0].compileShaders();
        mShaders[0].linkShaders();

        printf("Circle 5\n");
        mVao.bindVertexArray();
        mBuffer.bindBuffer();
        mBuffer.bufferData(atlas::gl::size<atlas::math::Vector>(numberOfVertices * 3),
            allCircleVertices, GL_STATIC_DRAW);
        mBuffer.vertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0,
            atlas::gl::bufferOffset<float>(0));
        mVao.enableVertexAttribArray(0);

        printf("Circle 6\n");
        auto var = mShaders[0].getUniformVariable("model");
        mUniforms.insert(UniformKey("model", var));

        var = mShaders[0].getUniformVariable("colour");
        mUniforms.insert(UniformKey("colour", var));

        printf("Circle 7\n");

        mBuffer.unBindBuffer();
        mVao.unBindVertexArray();
        mShaders[0].disableShaders();
        printf("Circle 8\n");
    }

    void Circle::renderGeometry()
    {
        printf("Circle 9\n");
        if (!mShaders[0].shaderProgramValid())
        {
            return;
        }


        printf("Circle 10\n");
        mShaders[0].enableShaders();
        mVao.bindVertexArray();

        glUniformMatrix4fv(mUniforms["model"], 1, GL_FALSE, &mModel[0][0]);
        printf("Circle 11\n");
        //glUniform4f(mUniforms["colour"], 0, 0, 0, 1);
        //int n = (int)(mNumIndices / 2) - 2;
        //glDrawArrays(GL_LINES, n, 4);


        printf("Circle 12\n");
        glPointSize(5.0f);
        float rgb = (127.0f / 255.0f);
        glUniform4f(mUniforms["colour"], rgb, rgb, rgb, 1);
        glDrawArrays(GL_LINE_STRIP, 0, numberOfVertices);

        printf("Circle 13\n");
        mVao.unBindVertexArray();
        mShaders[0].disableShaders();
        printf("Circle 14\n");
    }
}