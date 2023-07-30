#include "game/line.hpp"

Line::Line(std::vector<LineWaypoint *> waypoints) { v_waypoints = waypoints; }

position_t Line::GetNextStation(int index, LineDirection direction) {
  if (direction == LineDirection::FORWARD) {
    for (int i = index + 1; i < v_waypoints.size(); ++i) {
      return v_waypoints[i]->PositionCoordinates();
    }
  } else {
    for (int i = index - 1; i >= 0; --i) {
      return v_waypoints[i]->PositionCoordinates();
    }
  }
  return v_waypoints[0]->PositionCoordinates();
}
