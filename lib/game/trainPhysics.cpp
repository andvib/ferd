#include "game/trainPhysics.hpp"

#include <spdlog/spdlog.h>

#include <cmath>

TrainPhysics::TrainPhysics() {
  m_speed = {0, 0};
  m_max_speed = 0.001;
  m_acceleration = 0.00001;
  m_acc_direction = 1;
  m_pos = {0, 4};
  m_vector = {-1, 0};
  m_breaking_distance = calculateBreakingDistance(m_acceleration, m_max_speed);
}

TrainPhysics::TrainPhysics(position_t start_position, float acceleration) {
  m_speed = {0, 0};
  m_max_speed = 0.001;
  m_acceleration = acceleration;
  m_acc_direction = 1;
  m_pos = start_position;
  m_vector = {-1, 0};
  m_breaking_distance = calculateBreakingDistance(m_acceleration, m_max_speed);
}

void TrainPhysics::Update(clock_t delta_time_ms) {
  float curr_abs_speed = sqrt(pow(m_speed.x, 2) + pow(m_speed.y, 2));

  if ((curr_abs_speed > m_max_speed) && (m_acc_direction == 1)) {
    m_acc_direction = 0;
  }

  m_speed.x = (m_acceleration * m_acc_direction * m_vector.x * delta_time_ms) +
              m_speed.x;
  m_speed.y = (m_acceleration * m_acc_direction * m_vector.y * delta_time_ms) +
              m_speed.y;

  m_pos.x = m_pos.x + (m_speed.x * delta_time_ms) -
            (0.5 * m_acceleration * m_acc_direction * m_vector.x *
             delta_time_ms * delta_time_ms);
  m_pos.y = m_pos.y + (m_speed.y * delta_time_ms) -
            (0.5 * m_acceleration * m_acc_direction * m_vector.y *
             delta_time_ms * delta_time_ms);
}

void TrainPhysics::stop() { m_speed = {0, 0}; }

float calculateBreakingDistance(float acceleration, float max_speed) {
  float time_to_stop;
  float breaking_distance;

  if (acceleration == 0) {
    spdlog::error("Acceleration cannot be 0!");
    return -1;
  }

  if (acceleration > 0) {
    acceleration = acceleration * -1;
  }

  time_to_stop = -(max_speed / acceleration);
  breaking_distance = 0.5 * max_speed * time_to_stop;

  return breaking_distance;
}
