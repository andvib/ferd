#include "game/trainPhysics.hpp"

#include <cmath>

TrainPhysics::TrainPhysics()
{
    m_direction = -1;
    m_speed = 0;
    m_acceleration = 0.00001;
    m_pos = {0, 4};
}

TrainPhysics::TrainPhysics(position_t start_position, float acceleration)
{
    m_direction = -1;
    m_speed = 0;
    m_acceleration = acceleration;
    m_pos = start_position;
}

void TrainPhysics::Update(clock_t delta_time_ms)
{
    m_speed = (m_acceleration * m_direction * delta_time_ms) + m_speed;
    m_pos.x = m_pos.x + (m_speed * delta_time_ms)
              - (0.5 * m_acceleration * m_direction * delta_time_ms * delta_time_ms);
}

void TrainPhysics::changeDirection() {
    m_direction = -m_direction;
}

void TrainPhysics::stop() {
    m_speed = 0;
}
