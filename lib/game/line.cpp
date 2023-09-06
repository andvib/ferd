#include "game/line.hpp"

Line::Line(std::vector<LineWaypoint *> waypoints) { v_waypoints = waypoints; }

position_t Line::GetNextStation(int index, LineDirection direction) {
  if (direction == LineDirection::FORWARD) {
    return v_waypoints[index + 1]->PositionCoordinates();
  } else {
    return v_waypoints[index - 1]->PositionCoordinates();
  }
}
