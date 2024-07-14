#include "game/trainNavigator.hpp"

#include <spdlog/spdlog.h>

#include <cmath>

TrainNavigator::TrainNavigator() {}

TrainNavigator::TrainNavigator(Line *line) {
  p_line = line;
  m_line_context.index = 0;
  m_line_context.direction = LineDirection::FORWARD;
}

float TrainNavigator::distanceToStation(position_t current_position) {
  return p_line->GetNextStationDistance(m_line_context, current_position);
}

void TrainNavigator::updateLineContext() {
  using enum LineDirection;

  if (m_line_context.direction == FORWARD) {
    ++m_line_context.index;
    spdlog::debug("New index: {}", m_line_context.index);
  } else {
    --m_line_context.index;
    spdlog::debug("New index: {}", m_line_context.index);
  }

  if (m_line_context.index == (p_line->NumberOfStations() - 1)) {
    spdlog::debug("Reversing!");
    m_line_context.direction = BACKWARD;
  } else if (m_line_context.index == 0) {
    spdlog::debug("Forward!");
    m_line_context.direction = FORWARD;
  }
}

bool TrainNavigator::atWaypoint(position_t current_position) {
  if (p_line->GetNextWaypointDistance(m_line_context, current_position) < 0.1) {
    spdlog::debug("Train reached waypoint ({},{})", current_position.x,
                  current_position.y);
    updateLineContext();

    return true;
  }
  return false;
}

bool TrainNavigator::atStation(position_t current_position) {
  if (p_line->GetNextStationDistance(m_line_context, current_position) < 0.05) {
    spdlog::debug("Train reached station ({},{})", current_position.x,
                  current_position.y);
    updateLineContext();

    return true;
  }
  return false;
}

vector_t TrainNavigator::vectorToNextWaypoint(position_t current_position) {
  int err;
  position_t next_waypoint;

  err = p_line->GetNextWaypoint(&next_waypoint, m_line_context);
  if (err) {
    spdlog::error("Error when getting next waypoint ({}", err);
    return {0, 0};
  }

  float vector_length = sqrt(pow((next_waypoint.x - current_position.x), 2) +
                             pow((next_waypoint.y - current_position.y), 2));

  float x_vector = (next_waypoint.x - current_position.x) / vector_length;
  float y_vector = (next_waypoint.y - current_position.y) / vector_length;

  return {x_vector, y_vector};
}

position_t TrainNavigator::nextWaypointPos() {
  int err;
  position_t next_waypoint;

  err = p_line->GetNextWaypoint(&next_waypoint, m_line_context);
  if (err) {
    spdlog::error("Error when getting station {}", err);
    return {0, 0};
  }

  return next_waypoint;
}
