#include "game/line.hpp"

Line::Line(std::vector<Waypoint *> waypoints, struct ferd_color color)
    : v_waypoints(waypoints), m_color(color) {
  for (int i = 0; i < (v_waypoints.size() - 1); i++) {
    position_t point0 = v_waypoints[i]->PositionCoordinates();
    position_t point1 = v_waypoints[i + 1]->PositionCoordinates();
    struct line points = {
        .x0 = point0.x,
        .y0 = point0.y,
        .x1 = point1.x,
        .y1 = point1.y,
        .width = 0.7f,
    };

    auto temp_line = new LineObject(points, m_color);
    v_line_objects.push_back(temp_line);
  }
}

position_t Line::GetNextStation(int index, LineDirection direction) {
  if (direction == LineDirection::FORWARD) {
    return v_waypoints[index + 1]->PositionCoordinates();
  } else {
    return v_waypoints[index - 1]->PositionCoordinates();
  }
}
