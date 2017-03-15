#include "PythagorasTree.hpp"

#define PI 3.14159265358979323846
#define BRANCH_LENGTH 0.025f
#define LEAF_LENGTH 0.0125f

namespace assignment3
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

    PythagorasTree::PythagorasTree(std::string axiom) : _Buffer(GL_ARRAY_BUFFER), _lAxiom(axiom) {

        generateLSystem(0);

        std::vector<atlas::gl::ShaderUnit> shaders
        {
            { gridFS, GL_FRAGMENT_SHADER, true }
        };

        mShaders.push_back(atlas::gl::Shader(shaders));
        mShaders[0].compileShaders();
        mShaders[0].linkShaders();

        _Vao.bindVertexArray();

        _Buffer.bindBuffer();

        _Buffer.bufferData(atlas::gl::size<atlas::math::Point>(_Vertices.size()),
            _Vertices.data(), GL_DYNAMIC_DRAW);
        _Buffer.vertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0,
            atlas::gl::bufferOffset<float>(0));


        _Vao.enableVertexAttribArray(0);

        auto var = mShaders[0].getUniformVariable("colour");
        mUniforms.insert(UniformKey("colour", var));

        _Buffer.unBindBuffer();
        _Vao.unBindVertexArray();
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
        glDrawArrays(GL_LINES, 0, (int) _Vertices.size());

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
        std::cout << "Generating pythagoras tree structure for a recursion level of: " << recursionLevel << std::endl;
        _lSystem = _lAxiom;        
        recurse(_lSystem, recursionLevel);
        _Vertices.clear();

        Stack turtleStack;
        Point current_point = Point(0.0f, -0.8f, 0.0f);
        Point previous_point;
        float angle = 0;

        for (int i = 0; i < _lSystem.length(); i++)
        {
            char curr = _lSystem.at(i);
            previous_point = current_point;
            float x = 0.0f;
            float y = 0.0f;

            if (curr == '0')
            {
                x = sin(2 * PI * (angle / 360)) * LEAF_LENGTH;
                y = cos(2 * PI * (angle / 360)) * LEAF_LENGTH;
                current_point.x += x;
                current_point.y += y;
                _Vertices.push_back(previous_point);
                _Vertices.push_back(current_point);
            }
            else if (curr == '1')
            {
                x = sin(2 * PI * (angle / 360)) * BRANCH_LENGTH;
                y = cos(2 * PI * (angle / 360)) * BRANCH_LENGTH;
                current_point.x += x;
                current_point.y += y;
                _Vertices.push_back(previous_point);
                _Vertices.push_back(current_point);
            }
            else if (curr == '[')
            {
                turtleStack.push(TurtleValue(current_point, angle));
                angle -= 45.0f;
            }
            else if (curr == ']')
            {
                if (turtleStack.size() == 0)
                    break;

                TurtleValue value(turtleStack.top());
                angle = value.angle() + 45;
                current_point = value.position();
                turtleStack.pop();
            }
        }

        _Buffer.bindBuffer();

        _Buffer.bufferData(atlas::gl::size<atlas::math::Point>(_Vertices.size()),
            _Vertices.data(), GL_DYNAMIC_DRAW);

        _Buffer.unBindBuffer();
    }
}