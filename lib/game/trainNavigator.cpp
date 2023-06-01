#include "game/trainNavigator.hpp"

#include <cmath>

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
    int distance_to_station = current_position.x - m_next_station.x;
    if (abs(distance_to_station) < 0.001) {
        if (m_next_station.x == m_start_station.x) {
            m_next_station = m_end_station;
        } else {
            m_next_station = m_start_station;
        }
        return true;
    }
    return false;
}
