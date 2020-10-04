#include "Aircraft_Animation.h"


Aircraft_Animation::Aircraft_Animation()
{
	this->m_model_mat = glm::mat4(1.0f);
}


Aircraft_Animation::~Aircraft_Animation()
{
}

void Aircraft_Animation::init()
{
	reset();
}

void Aircraft_Animation::init(Curve* animation_curve)
{
	m_animation_curve = animation_curve;
	reset();
}

void Aircraft_Animation::update(float delta_time)
{

}

void Aircraft_Animation::reset()
{
	m_model_mat = glm::mat4(1.0f);
	nextindex = 0;
	index = 0;

	if (m_animation_curve != nullptr && m_animation_curve->control_points_pos.size() > 0)
	{
		m_model_mat = glm::translate(m_model_mat, m_animation_curve->control_points_pos[0]);
	}
	
}

void Aircraft_Animation::animate() {
	finish = std::chrono::high_resolution_clock::now();
	elapsed = finish - start;
	float d = 0.0;
	float v0 = 2.0f / (t2 - t1 + 1.0f);

	if (elapsed.count() < total_moving_time) {
		norm_time = elapsed.count() / total_moving_time;
	}

	if (norm_time > 0.0 && norm_time <= t1) {
		float a1 = pow(norm_time, 2);
		float a2 = 2 * t1;
		d = v0 * a1 / a2;
		for (int i = index; i < m_animation_curve->lengths.size(); i++) {
			if (m_animation_curve->lengths.at(i) >= d) {
				nextindex = i;
				break;
			}
		}
		glm::vec3 move = m_animation_curve->curve_points_pos[nextindex] - m_animation_curve->curve_points_pos[index];
		m_model_mat = glm::translate(m_model_mat, move);
		index = nextindex;
	}
	if (norm_time > t1 && norm_time <= t2) {
		float b1 = t1 / 2;
		float b2 = norm_time - t1;
		d = (v0 * b1) + (v0 * b2);
		for (int i = index; i < m_animation_curve->lengths.size(); i++) {
			if (m_animation_curve->lengths.at(i) >= d) {
				nextindex = i;
				break;
			}
		}
		glm::vec3 move = m_animation_curve->curve_points_pos[nextindex] - m_animation_curve->curve_points_pos[index];
		m_model_mat = glm::translate(m_model_mat, move);
		index = nextindex;
	}
	if (norm_time > t2 && norm_time <= 1.0) {
		float a = v0 * (t1 / 2);
		float b = v0 * (t2 - t1);
		float c1 = norm_time - t2;
		float c2 = 2 * (1 - t2);
		float c3 = 1.0 - (c1 / c2);
		float c = v0 * c3 * c1;
		d = a + b + c;
		for (int i = index; i < m_animation_curve->lengths.size(); i++) {
			if (m_animation_curve->lengths.at(i) >= d) {
				nextindex = i;
				break;
			}
		}
		glm::vec3 move = m_animation_curve->curve_points_pos[nextindex] - m_animation_curve->curve_points_pos[index];
		m_model_mat = glm::translate(m_model_mat, move);
		index = nextindex;
	}

}

void Aircraft_Animation::time_start() {
	start = std::chrono::high_resolution_clock::now();
}
