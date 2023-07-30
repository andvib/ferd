#include "game/trainNavigator.hpp"

#include <spdlog/spdlog.h>

#include <cmath>

TrainNavigator::TrainNavigator() {}

TrainNavigator::TrainNavigator(Line *line) {
  p_line = line;
  m_waypoint_index = 0;
  m_direction = LineDirection::FORWARD;
}

float TrainNavigator::distanceToStation(position_t current_position) {
  position_t next_station =
      p_line->GetNextStation(m_waypoint_index, m_direction);
  return sqrt(pow((current_position.x - next_station.x), 2) +
              pow((current_position.y - next_station.y), 2));
}

bool TrainNavigator::atStation(position_t current_position) {
  position_t next_station =
      p_line->GetNextStation(m_waypoint_index, m_direction);
  float distance_to_station =
      sqrt(pow((current_position.x - next_station.x), 2) +
           pow((current_position.y - next_station.y), 2));

  if (distance_to_station < 0.01) {
    spdlog::debug("Train reached station ({},{})", current_position.x,
                  current_position.y);

    if (m_direction == LineDirection::FORWARD) {
      ++m_waypoint_index;
      spdlog::debug("New index: {}", m_waypoint_index);
    } else {
      --m_waypoint_index;
      spdlog::debug("New index: {}", m_waypoint_index);
    }

    if (m_waypoint_index == (p_line->NumberOfStations() - 1)) {
      spdlog::debug("Reversing!");
      m_direction = LineDirection::BACKWARD;
    } else if (m_waypoint_index == 0) {
      spdlog::debug("Forward!");
      m_direction = LineDirection::FORWARD;
    }

    return true;
  }
  return false;
}

vector_t TrainNavigator::vectorToNextStation(position_t current_position) {
  position_t next_station =
      p_line->GetNextStation(m_waypoint_index, m_direction);

  float vector_length = sqrt(pow((next_station.x - current_position.x), 2) +
                             pow((next_station.y - current_position.y), 2));

  float x_vector = (next_station.x - current_position.x) / vector_length;
  float y_vector = (next_station.y - current_position.y) / vector_length;

  return {x_vector, y_vector};
}
