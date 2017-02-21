#include "ControlPoints.h"
#include "atlas/gl/Shader.hpp"
#include <math.h>


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

    //Instantiate Control Points
	ControlPoints::ControlPoints() :
		mBuffer(GL_ARRAY_BUFFER)
	{
		mModel = atlas::math::Matrix4(1.0f);

		std::vector<atlas::gl::ShaderUnit> shaders
		{
			{ gridFS, GL_FRAGMENT_SHADER, true }
		};

		mShaders.push_back(atlas::gl::Shader(shaders));
		mShaders[0].compileShaders();
		mShaders[0].linkShaders();

		mVao.bindVertexArray();
		mBuffer.bindBuffer();
		mBuffer.bufferData(atlas::gl::size<atlas::math::Vector>(_positions.size()),
			_positions.data(), GL_STREAM_DRAW);
		mBuffer.vertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0,
			atlas::gl::bufferOffset<float>(0));
		mVao.enableVertexAttribArray(0);

		auto var = mShaders[0].getUniformVariable("colour");
		mUniforms.insert(UniformKey("colour", var));

		mBuffer.unBindBuffer();
		mVao.unBindVertexArray();
		mShaders[0].disableShaders();
	}

    //Render Buffered Objects
	void ControlPoints::renderGeometry()
	{
		if (!mShaders[0].shaderProgramValid())
		{
			return;
		}

		mShaders[0].enableShaders();
		mVao.bindVertexArray();

		float rgb = 0.0f;
		glUniform4f(mUniforms["colour"], rgb, rgb, rgb, 1);

		if (drawLines)
		{
			glDrawArrays(GL_LINE_STRIP, 0, _positions.size());
		}
		
		glPointSize(10.0f);
		glDrawArrays(GL_POINTS, 0, _positions.size());

		mVao.unBindVertexArray();
		mShaders[0].disableShaders();
	}

    bool ControlPoints::intersectsPoint(const double xPos, const double yPos, const double threshold)
    {
        if (abs(_xPos - xPos) < threshold && abs(_yPos - yPos) < threshold)
        {
            return true;
        }
        return false;
    }

    //Update Buffere Objects
	void ControlPoints::updateObjects()
	{
		mBuffer.bindBuffer();
		mBuffer.bufferData(atlas::gl::size<atlas::math::Vector>(_positions.size()),
			_positions.data(), GL_STREAM_DRAW);
		mBuffer.vertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0,
			atlas::gl::bufferOffset<float>(0));
		mBuffer.unBindBuffer();
	}

}