#pragma once

# define PI   3.1415

namespace  Astr1 {

	class Line
	{
	private:
		/*double x;
		double y;*/
		double radius;
	public:
		Line(double input_radius = 1);

		double get_radius() const { return radius; }
		void set_radius(double input_radius = 1);

		double distance(double t) const;

		double area() const;
		double length() const;
		double curvature(double t) const;
		void coordinates(double t) const;
		double coordinates_dec(double x) const;



	};
};
