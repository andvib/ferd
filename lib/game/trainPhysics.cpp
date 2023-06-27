#include "game/trainPhysics.hpp"

#include <cmath>

#include <spdlog/spdlog.h>

TrainPhysics::TrainPhysics()
{
    m_speed = {0, 0};
    m_acceleration = 0.00001;
    m_pos = {0, 4};
    m_vector = {-1, 0};
}

TrainPhysics::TrainPhysics(position_t start_position, float acceleration)
{
    m_speed = {0, 0};
    m_acceleration = acceleration;
    m_pos = start_position;
    m_vector = {-1, 0};
}

void TrainPhysics::Update(clock_t delta_time_ms)
{
    m_speed.x = (m_acceleration * m_vector.x * delta_time_ms) + m_speed.x;
    m_speed.y = (m_acceleration * m_vector.y * delta_time_ms) + m_speed.y;

    m_pos.x = m_pos.x + (m_speed.x * delta_time_ms)
              - (0.5 * m_acceleration * delta_time_ms * delta_time_ms);
    m_pos.y = m_pos.y + (m_speed.y * delta_time_ms)
              - (0.5 * m_acceleration * delta_time_ms * delta_time_ms);
}

void TrainPhysics::stop() {
    m_speed = {0, 0};
}
