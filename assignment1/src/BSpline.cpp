#include "BSpline.h"
#include "atlas/gl/Shader.hpp"
#include <vector>
#include <iostream>


namespace assignment1
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
    BSpline::BSpline() :
        mBuffer(GL_ARRAY_BUFFER),
        mBuffer_knots(GL_ARRAY_BUFFER),
        mBuffer_basis_function(GL_ARRAY_BUFFER)
    {
        std::vector<atlas::gl::ShaderUnit> shaders
        {
            { gridFS, GL_FRAGMENT_SHADER, true }
        };

        setOrderAndDegree(3);
        generateKnots();
        generateBasisFunctions();
        calculateBSplinePoints(200, order, knots);

        mShaders.push_back(atlas::gl::Shader(shaders));
        mShaders[0].compileShaders();
        mShaders[0].linkShaders();

        //BSplines
        mVao.bindVertexArray();
        mBuffer.bindBuffer();
        mBuffer.bufferData(atlas::gl::size<atlas::math::Vector>(BSplinePoints.size()),
            BSplinePoints.data(), GL_DYNAMIC_DRAW);
        mBuffer.vertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0,
            atlas::gl::bufferOffset<float>(0));
        mVao.enableVertexAttribArray(0);

        auto var = mShaders[0].getUniformVariable("colour");
        mUniforms.insert(UniformKey("colour", var));

        mBuffer.unBindBuffer();
        mVao.unBindVertexArray();

        //knots
        mVao_knots.bindVertexArray();
        mBuffer_knots.bindBuffer();
        mBuffer_knots.bufferData(atlas::gl::size<atlas::math::Vector>(knots_coords.size()),
            knots_coords.data(), GL_DYNAMIC_DRAW);
        mBuffer_knots.vertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0,
            atlas::gl::bufferOffset<float>(0));
        mVao_knots.enableVertexAttribArray(0);

        mBuffer_knots.unBindBuffer();
        mVao_knots.unBindVertexArray();

        //basisFunctions
        mVao_basis_functions.bindVertexArray();
        mBuffer_basis_function.bindBuffer();
        mBuffer_basis_function.bufferData(atlas::gl::size<atlas::math::Vector>(basis_functions.size()),
            basis_functions.data(), GL_DYNAMIC_DRAW);
        mBuffer_basis_function.vertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0,
            atlas::gl::bufferOffset<float>(0));
        mVao_basis_functions.enableVertexAttribArray(0);

        mBuffer_basis_function.unBindBuffer();
        mVao_basis_functions.unBindVertexArray();

        mShaders[0].disableShaders();
    }

    //Render the generated splines
    void BSpline::renderGeometry()
    {
        if (!mShaders[0].shaderProgramValid())
        {
            return;
        }

        if (controlPoints.getNumberOfPoints() > order)
        {

            mShaders[0].enableShaders();
            mVao.bindVertexArray();

            float rgb = 0.0f;
            glUniform4f(mUniforms["colour"], 255.0f, rgb, rgb, 1);

            glDrawArrays(GL_LINE_STRIP, 0, BSplinePoints.size());

            mVao.unBindVertexArray();

            mVao_knots.bindVertexArray();

            rgb = 0.0f;
            glUniform4f(mUniforms["colour"], rgb, rgb, 255.0f, 1);

            glPointSize(10.0f);
            glDrawArrays(GL_POINTS, 0, knots.size());

            mVao_knots.unBindVertexArray();

            mVao_basis_functions.bindVertexArray();

            rgb = 0.0f;
            glUniform4f(mUniforms["colour"], rgb, 255.0f, rgb, 1);

            glPointSize(10.0f);
            glDrawArrays(GL_LINES, 0, basis_functions.size());
            
            mVao_basis_functions.unBindVertexArray();
            mShaders[0].disableShaders();
        }
        //Render Control Points
        controlPoints.renderGeometry();

    }

    //Deboor Cox algorithm
    float BSpline::deBoorCox(float u, int i, int k, Knots knots)
    {
        if (k == 1)
        {
            if (knots.at(i) <= u && u < knots.at(i + 1))
            {
                return 1.0f;
            }
            else
            {
                return 0.0f;
            }
        }

        float denomA = knots.at(i + k - 1) - knots.at(i);
        float denomB = knots.at(i + k) - knots.at(i + 1);

        float EqnA = 0.0f;
        float EqnB = 0.0f;
        if (denomA > 0.0f)
        {
            EqnA = ((u - knots.at(i)) / denomA) * deBoorCox(u, i, k - 1, knots);
        }
        if (denomB> 0.0f)
        {
            EqnB = ((knots.at(i + k) - u) / denomB) * deBoorCox(u, i + 1, k - 1, knots);
        }
        return EqnA + EqnB;
    }

    //Calculate the spline points to be rendered.
    void BSpline::calculateBSplinePoints(int levelOfDetail, int k, Knots knots)
    {
        basis_functions.clear();
        std::vector<Vector3> points = controlPoints.getPositions();
        BSplinePoints.clear();
        for (int i = 0; i != levelOfDetail; ++i)
        {
            float u = (float)(i) / (float)(levelOfDetail - 1);
            if (i == levelOfDetail - 1)
                u -= 0.001f;

            Vector3 q(0.0f, 0.0f, 0.0f);
            for (int j = 0; j < points.size(); j++)
            {
                float deBoorVal = deBoorCox(u, j, k, knots);
                basis_functions.push_back(Vector3(-0.5f + u, deBoorVal * 0.5 - 0.95f, 0.0f));
                q += points.at(j) * deBoorVal;
            }
            
            BSplinePoints.push_back(q);
        }
    }

    void BSpline::setOrderAndDegree(int deg)
    {
        degree = deg;
        order = deg + 1;
    }

    //Generate the knots for the deboor Cox algorithm
    void BSpline::generateKnots()
    {
        knots.clear();
        int numberOfControlPoints = controlPoints.getNumberOfPoints();

        for (int i = 0; i < order; ++i)
        {
            knots.push_back(0.0f);
        }

        int knotSize = numberOfControlPoints + order;
        int numNormalized = (knotSize - 2 * order) + 1;
        for (int i = 1; i < numNormalized; ++i)
        {
            knots.push_back(i * 1.0f / numNormalized);
        }


        for (int i = 0; i < order; ++i)
        {
            knots.push_back(1.0f);
        }
    }

    void BSpline::generateBasisFunctions()
    {

    }

    //Add a Control Point
    void BSpline::addControlPoint(double x, double y)
    {
        controlPoints.addPosition(x, y);
        updateSpline();
    }

    //Update spline after changes
    void BSpline::updateSpline()
    {
        generateKnots();
        knots_coords.clear();
        for (int i = 0; i < knots.size(); i++)
        {
            atlas::math::Vector vec3(-0.5f + knots.at(i), -0.95f, 0.0f);
            knots_coords.push_back(vec3);
        }
        calculateBSplinePoints(100, order, knots);
        updateBuffer();
        renderGeometry();
    }


    int BSpline::getNumberOfControlPoints()
    {
        return controlPoints.getNumberOfPoints();
    }

    void BSpline::removeControlPoint()
    {
        controlPoints.removeEndPoint();
        updateSpline();
    }

    int BSpline::getDegree()
    {
        return degree;
    }


    //update buffered data
    void BSpline::updateBuffer()
    {
        //Bspline
        mBuffer.bindBuffer();
        mBuffer.bufferData(atlas::gl::size<atlas::math::Vector>(BSplinePoints.size()),
            BSplinePoints.data(), GL_DYNAMIC_DRAW);
        mBuffer.unBindBuffer();

        //basis functions
        mBuffer_basis_function.bindBuffer();
        mBuffer_basis_function.bufferData(atlas::gl::size<atlas::math::Vector>(basis_functions.size()),
            basis_functions.data(), GL_DYNAMIC_DRAW);
        mBuffer_basis_function.unBindBuffer();

        //knots
        mBuffer_knots.bindBuffer();
        mBuffer_knots.bufferData(atlas::gl::size<atlas::math::Vector>(knots_coords.size()),
            knots_coords.data(), GL_DYNAMIC_DRAW);
        mBuffer_knots.unBindBuffer();
    }
}