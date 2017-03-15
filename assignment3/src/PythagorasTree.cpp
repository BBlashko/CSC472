#include "PythagorasTree.hpp"
#include <atlas/gl/GL.hpp>
#include "atlas/gl/Shader.hpp"
#include <atlas/utils/GUI.hpp>
#include <iostream>
#include <stack>

#define BRANCH_LENGTH 0.1f
#define LEAF_LENGTH 0.05f

namespace assignment3
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

    PythagorasTree::PythagorasTree(std::string axiom) : _Buffer(GL_ARRAY_BUFFER), _lAxiom(axiom) {

        std::vector<atlas::gl::ShaderUnit> shaders
        {
            { gridVs, GL_VERTEX_SHADER, true },
            { gridFS, GL_FRAGMENT_SHADER, true }
        };

        mShaders.push_back(atlas::gl::Shader(shaders));
        mShaders[0].compileShaders();
        mShaders[0].linkShaders();

        auto var = mShaders[0].getUniformVariable("colour");
        mUniforms.insert(UniformKey("colour", var));
        mShaders[0].disableShaders();
    };


    void PythagorasTree::renderGeometry()
    {
        if (!mShaders[0].shaderProgramValid())
        {
            return;
        }

        mShaders[0].enableShaders();
        _Vao.bindVertexArray();

        glUniform4f(mUniforms["colour"],  0, 0, 0, 1);
        glDrawArrays(GL_LINES, 0, (int) _NumIndices);

        _Vao.unBindVertexArray();
        mShaders[0].disableShaders();
    }

    void PythagorasTree::recurse(std::string &system, int n)
    {
        if (n == 0)
        {
            return;
        }

        int size = system.length();
        for (int i = 0; i < system.length(); i++)
        {
            char c = system.at(i);

            if (c == '0')
            {
                system.erase(i, 1);
                system.insert(i, "1[0]0");
                i += 5;
            }
            else if (c == '1')
            {
                system.erase(i, 1);
                system.insert(i, "11");
                i += 1;
            }
        }
        recurse(system, n - 1);
    }

    void PythagorasTree::generateLSystem(int recursionLevel)
    {
        _lSystem = _lAxiom;
        recurse(_lSystem, recursionLevel);

        Stack turtleStack;
        Point current_point = Point(0.0f, 0.0f, 0.0f);
        Point next_point;
        int angle = 0;

        _Vertices.push_back(current_point);
        for (int i = 0; i < _lSystem.length(); i++)
        {
            next_point = current_point;
            switch (_lSystem.at(i))
            {
            case '0':
                next_point.y += LEAF_LENGTH;
                break;
            case '1':
                next_point.y += BRANCH_LENGTH;
                break;
            case '[':
                angle += 45;
                turtleStack.push(next_point, angle);
                
                break;
            case ']':
                break;
            default:
                break;
            }
        }
    }
}