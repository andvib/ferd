#include "game/trainPhysics.hpp"

#include <spdlog/spdlog.h>

#include <cmath>

TrainPhysics::TrainPhysics() {
  m_speed = {0, 0};
  m_max_speed = 6;    /* m/s */
  m_acceleration = 1; /* m / s^2 */
  m_acc_direction = 1;
  m_pos = {0, 4};
  m_vector = {-1, 0};
}

TrainPhysics::TrainPhysics(position_t start_position, float acceleration) {
  m_speed = {0, 0};
  m_max_speed = 10;              /* m/s */
  m_acceleration = acceleration; /* m / s^2 */
  m_acc_direction = 1;
  m_pos = start_position;
  m_vector = {-1, 0};
}

void TrainPhysics::Update(clock_t delta_time_ms) {
  float curr_abs_speed = sqrt(pow(m_speed.x, 2) + pow(m_speed.y, 2));
  float delta_time_s = delta_time_ms / 1000.0;

  if ((curr_abs_speed > m_max_speed) && (m_acc_direction == 1)) {
    m_acc_direction = 0;
  }

  m_speed.x = (m_acceleration * m_acc_direction * m_vector.x * delta_time_s) +
              m_speed.x;
  m_speed.y = (m_acceleration * m_acc_direction * m_vector.y * delta_time_s) +
              m_speed.y;

  m_pos.x = m_pos.x + (m_speed.x * delta_time_s) -
            (0.5 * m_acceleration * m_acc_direction * m_vector.x *
             delta_time_s * delta_time_s);
  m_pos.y = m_pos.y + (m_speed.y * delta_time_s) -
            (0.5 * m_acceleration * m_acc_direction * m_vector.y *
             delta_time_s * delta_time_s);
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
