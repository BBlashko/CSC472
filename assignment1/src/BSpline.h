#pragma once
#include "atlas/utils/Geometry.hpp"
#include "atlas/gl/VertexArrayObject.hpp"
#include "atlas/gl/Buffer.hpp"
#include "ControlPoints.h"
#include "BSpline.h"
#include <vector>

namespace assignment1
{
	class BSpline : public atlas::utils::Geometry
	{
		using Vector3 = atlas::math::Vector;
        using Knots = std::vector<float>;

	public:
		BSpline::BSpline();

		void renderGeometry() override;
		void setDrawLines(bool b);
        void setControlPointPositions(std::vector<Vector3>);
        void setOrderAndDegree(int deg);
        void addControlPoint(double x, double y);
        int getNumberOfControlPoints();
        void removeControlPoint();
        int getDegree();
        void generateKnots();
        void BSpline::updateSpline();

	private:
        float deBoorCox(float u, int i, int k, Knots knots);
        void BSpline::calculateBSplinePoints(int levelOfDetail, int k, Knots knots);
        void BSpline::updateBuffer();

		atlas::gl::VertexArrayObject mVao;
		atlas::gl::Buffer mBuffer;
        atlas::gl::VertexArrayObject mVao_knots;
        atlas::gl::Buffer mBuffer_knots;

        std::vector<float> knots;
        std::vector<atlas::math::Vector> knots_coords;
        std::vector<Vector3> BSplinePoints;
        ControlPoints controlPoints;

        int degree;
        int order;

		bool drawLines = true;
	};
}