#pragma once

#include <vector>
#include <iostream>
#include <chrono>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Curve.h"

class Aircraft_Animation
{

public:
	float total_moving_time = 10.0f;
	float t1 = 0.1f;
	float t2 = 0.7f;
	bool is_moving = false;
	std::chrono::time_point<std::chrono::high_resolution_clock> start;
	std::chrono::time_point<std::chrono::high_resolution_clock> finish;
	std::chrono::duration<double> elapsed;
	float norm_time = 0.0f;
	int nextindex = 0;
	int index = 0;

private:
	glm::mat4 m_model_mat;
	Curve* m_animation_curve = nullptr;

public:
	Aircraft_Animation();
	~Aircraft_Animation();

	void init();
	void init(Curve* animation_curve);

	void update(float delta_time);

	void reset();
	glm::mat4 get_model_mat() { return m_model_mat; };
	void animate();
	void time_start();
};

