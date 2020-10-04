#pragma once
#include <vector>
#include <iostream>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Curve
{
public:
	Curve();
	~Curve();
	
	void init();
	void calculate_curve();
	
public:
	float tau = 0.5; // Coefficient for catmull-rom spline
	int num_points_per_segment = 200;
	bool curve_enabled = true;

	std::vector<glm::vec3> control_points_pos;
	std::vector<glm::vec3> curve_points_pos;
	std::vector<float> lengths;
	std::vector<float> param;

	float GetT(float t, glm::vec3 p0, glm::vec3 p1) {
		float a = pow((p1.x - p0.x), 2) + pow((p1.y - p0.y), 2) + pow((p1.z - p0.z), 2);
		float b = pow(a, tau * .5);
		return (b + t);
	}

	void Catmull_Rom(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3)
	{
		float t0 = 0.0f;
		float t1 = GetT(t0, p0, p1);
		float t2 = GetT(t1, p1, p2);
		float t3 = GetT(t2, p2, p3);

		for (float t = t1; t < t2; t += ((t2 - t1) / (float)num_points_per_segment))
		{
			glm::vec3 A1 = (t1 - t) / (t1 - t0) * p0 + (t - t0) / (t1 - t0) * p1;
			glm::vec3 A2 = (t2 - t) / (t2 - t1) * p1 + (t - t1) / (t2 - t1) * p2;
			glm::vec3 A3 = (t3 - t) / (t3 - t2) * p2 + (t - t2) / (t3 - t2) * p3;

			glm::vec3 B1 = (t2 - t) / (t2 - t0) * A1 + (t - t0) / (t2 - t0) * A2;
			glm::vec3 B2 = (t3 - t) / (t3 - t1) * A2 + (t - t1) / (t3 - t1) * A3;

			glm::vec3 C = (t2 - t) / (t2 - t1) * B1 + (t - t1) / (t2 - t1) * B2;

			curve_points_pos.push_back(C);
		}
	}
	void calculate_arclengths() {
		lengths.clear();
		param.clear();
		float n = 0.0f;

		for (unsigned int i = 0; i < curve_points_pos.size() - 1; i++) {
			float a = pow(curve_points_pos[i + 1].x - curve_points_pos[i].x, 2);
			float b = pow(curve_points_pos[i + 1].y - curve_points_pos[i].y, 2);
			float c = pow(curve_points_pos[i + 1].z - curve_points_pos[i].z, 2);
			float d = pow(a + b + c, .5);
			n += d;
			lengths.push_back(n);
			param.push_back((float)i / 1605);
		}
		for (unsigned int i = 0; i < lengths.size(); i++) {
			lengths[i] /= lengths.back();
		}
	}
};