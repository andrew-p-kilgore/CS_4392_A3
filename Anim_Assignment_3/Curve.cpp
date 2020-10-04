#include "Curve.h"

Curve::Curve()
{
}

Curve::~Curve()
{
}

void Curve::init()
{
	this->control_points_pos = {
		{ 0.0, 8.5, -2.0 },
		{ -3.0, 11.0, 2.3 },
		{ -6.0, 8.5, -2.5 },
		{ -4.0, 5.5, 2.8 },
		{ 1.0, 2.0, -4.0 },
		{ 4.0, 2.0, 3.0 },
		{ 7.0, 8.0, -2.0 },
		{ 3.0, 10.0, 3.7 }
	};
	calculate_curve();
	calculate_arclengths();
}

void Curve::calculate_curve()
{
	if (curve_enabled) {
		glm::vec3 p0 = this->control_points_pos[0];
		glm::vec3 p1 = this->control_points_pos[1];
		glm::vec3 p2 = this->control_points_pos[2];
		glm::vec3 p3 = this->control_points_pos[3];
		glm::vec3 p4 = this->control_points_pos[4];
		glm::vec3 p5 = this->control_points_pos[5];
		glm::vec3 p6 = this->control_points_pos[6];
		glm::vec3 p7 = this->control_points_pos[7];
		this->Catmull_Rom(p7, p0, p1, p2);
		this->Catmull_Rom(p0, p1, p2, p3);
		this->Catmull_Rom(p1, p2, p3, p4);
		this->Catmull_Rom(p2, p3, p4, p5);
		this->Catmull_Rom(p3, p4, p5, p6);
		this->Catmull_Rom(p4, p5, p6, p7);
		this->Catmull_Rom(p5, p6, p7, p0);
		this->Catmull_Rom(p6, p7, p0, p1);
	}
	else
		this->curve_points_pos.clear();

}
