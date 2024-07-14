#include "game/trainPhysics.hpp"

#include <spdlog/spdlog.h>

#include <cmath>
#include <iostream>

TrainPhysics::TrainPhysics() : m_pos(0, 0) {
  m_max_speed = 6;    /* m/s */
  m_acceleration = 1; /* m / s^2 */
  m_acc_direction = 1;
}

TrainPhysics::TrainPhysics(position_t start_position, float acceleration)
    : m_pos(start_position.x, start_position.y) {
  m_max_speed = 10;              /* m/s */
  m_acceleration = acceleration; /* m / s^2 */
  m_acc_direction = 1;
}

void TrainPhysics::rotateTrain(vector_t vector) {
  m_vector(0) = vector.x;
  m_vector(1) = vector.y;

  float curr_abs_speed = absoluteSpeed(m_speed);
  m_speed = curr_abs_speed * m_vector;
}

void TrainPhysics::Update(clock_t delta_time_ms) {
  float curr_abs_speed = absoluteSpeed(m_speed);
  float delta_time_s = delta_time_ms / 1000.0;

  if ((curr_abs_speed > m_max_speed) && (m_acc_direction == 1)) {
    m_acc_direction = 0;
  }

  m_speed =
      (m_acceleration * m_acc_direction * m_vector * delta_time_s) + m_speed;

  m_pos = m_pos + (m_speed * delta_time_s) -
          (0.5 * m_acceleration * m_acc_direction * m_vector * delta_time_s *
           delta_time_s);
}

void TrainPhysics::stop() { m_speed = {0, 0}; }

float TrainPhysics::calculateBreakingDistance(float acceleration,
                                              float speed) const {
  if (acceleration == 0) {
    spdlog::error("Acceleration cannot be 0!");
    return -1;
  }

  if (acceleration > 0) {
    acceleration = acceleration * -1;
  }

  return -(speed * speed) / (2 * acceleration);
}
