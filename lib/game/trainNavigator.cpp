#include "game/trainNavigator.hpp"

#include <cmath>
#include <spdlog/spdlog.h>

TrainNavigator::TrainNavigator()
{
}

TrainNavigator::TrainNavigator(position_t start_station, position_t end_station)
{
    m_start_station = start_station;
    m_end_station = end_station;
    m_next_station = end_station;
}

bool TrainNavigator::atStation(position_t current_position)
{
    float distance_to_station = sqrt(pow((current_position.x - m_next_station.x), 2) + pow((current_position.y - m_next_station.y), 2));

    if (distance_to_station < 0.05) {
        spdlog::debug("Train reached station ({},{})", current_position.x, current_position.y);
        if (m_next_station.x == m_start_station.x) {
            m_next_station = m_end_station;
        } else {
            m_next_station = m_start_station;
        }
        return true;
    }
    return false;
}

vector_t TrainNavigator::vectorToNextStation()
{
    position_t prev_station = (m_next_station.x == m_start_station.x) ? m_end_station : m_start_station;

    float vector_length = sqrt(pow((m_next_station.x - prev_station.x), 2) + pow((m_next_station.y - prev_station.y), 2));

    float x_vector = (m_next_station.x - prev_station.x) / vector_length;
    float y_vector = (m_next_station.y - prev_station.y) / vector_length;

    return {x_vector, y_vector};
}
