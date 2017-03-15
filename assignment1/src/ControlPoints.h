#pragma once

#include "atlas/utils/Geometry.hpp"
#include "atlas/gl/VertexArrayObject.hpp"
#include "atlas/gl/Buffer.hpp"

namespace assignment1
{
	class ControlPoints : public atlas::utils::Geometry
	{
		using Vector3 = atlas::math::Vector;

	public:
		ControlPoints::ControlPoints();

		void addPosition(double xPos, double yPos, double zPos);
		std::vector<Vector3>& getPositions();

		void updateObjects();
		void renderGeometry() override;
		void setDrawLines(bool b);
        int getNumberOfPoints();
        void removeEndPoint();

	private:
		atlas::gl::VertexArrayObject mVao;
		atlas::gl::Buffer mBuffer;

		std::vector<Vector3> _positions;

		double _xPos, _yPos, _zPos;
		bool drawLines = true;
	};

	inline void ControlPoints::addPosition(double xPos = 0.0, double yPos = 0.0, double zPos = 0.0)
	{
		Vector3 vec3 = Vector3(xPos, yPos, zPos);
		_positions.push_back(vec3);
		updateObjects();
	};

	inline std::vector<atlas::math::Vector>& ControlPoints::getPositions()
	{
		return _positions;
	}

	inline void ControlPoints::setDrawLines(bool b)
	{
		drawLines = b;
	};

    inline int ControlPoints::getNumberOfPoints()
    {
        return _positions.size();
    };

    inline void ControlPoints::removeEndPoint()
    {
        _positions.pop_back();
    };
}
