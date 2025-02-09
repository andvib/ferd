#include "game/line.hpp"

#include <spdlog/spdlog.h>

#include <memory>

Line::Line(std::vector<Waypoint*> waypoints, struct ferd_color color,
           std::shared_ptr<OpenGLWrapper> opengl)
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

    auto temp_line = make_shared<LineObject>(points, m_color, opengl);
    v_line_objects.push_back(temp_line);
  }
}

int Line::GetNextWaypoint(position_t* waypoint_pos, line_ctx ctx) {
  if (waypoint_pos == nullptr) {
    spdlog::error("Null pointer received");
    return -1;
  }

  if (((ctx.index == (NumberOfStations() - 1)) &&
       (ctx.direction == LineDirection::FORWARD)) ||
      ((ctx.index == 0) && (ctx.direction == LineDirection::BACKWARD))) {
    spdlog::error("Line context is out of bounds");
    return -1;
  }

  if (ctx.direction == LineDirection::FORWARD) {
    *waypoint_pos = v_waypoints[ctx.index + 1]->PositionCoordinates();
  } else {
    *waypoint_pos = v_waypoints[ctx.index - 1]->PositionCoordinates();
  }

  return 0;
}

int Line::GetNextStation(position_t* waypoint_pos, line_ctx ctx) {
  if (waypoint_pos == nullptr) {
    spdlog::error("Nullptr received");
    return -1;
  }

  if (((ctx.index == (NumberOfStations() - 1)) &&
       (ctx.direction == LineDirection::FORWARD)) ||
      ((ctx.index == 0) && (ctx.direction == LineDirection::BACKWARD))) {
    spdlog::error("Line context is out of bounds");
    return -1;
  }

  if (ctx.direction == LineDirection::FORWARD) {
    for (int i = ctx.index; i < NumberOfStations(); ++i) {
      Waypoint* waypoint = v_waypoints[i + 1];
      if (const auto* stationPtr = dynamic_cast<Station*>(waypoint)) {
        *waypoint_pos = waypoint->PositionCoordinates();
        return 0;
      }
    }
  } else {
    for (int i = ctx.index; i >= 0; --i) {
      Waypoint* waypoint = v_waypoints[i - 1];
      if (const auto* stationPtr = dynamic_cast<Station*>(waypoint)) {
        *waypoint_pos = waypoint->PositionCoordinates();
        return 0;
      }
    }
  }

  spdlog::error("No more stations on line");
  return -1;
}

float Line::GetNextWaypointDistance(line_ctx context,
                                    position_t current_position) {
  int err;
  position_t next_waypoint;

  err = GetNextWaypoint(&next_waypoint, context);
  if (err) {
    spdlog::error("Error occurred when getting next waypoint! {}", err);
    return -1;
  }

  return positionDistance(current_position, next_waypoint);
}

float Line::GetNextStationDistance(line_ctx context,
                                   position_t current_position) {
  float distance = 0;
  bool station_found = false;
  position_t prev_position = current_position;

  while (!station_found) {
    Waypoint* next_waypoint;

    if (context.direction == LineDirection::FORWARD) {
      next_waypoint = v_waypoints[context.index + 1];
    } else {
      next_waypoint = v_waypoints[context.index - 1];
    }

    distance +=
        positionDistance(prev_position, next_waypoint->PositionCoordinates());

    if (const auto* stationPtr = dynamic_cast<Station*>(next_waypoint)) {
      return distance;
    }

    spdlog::debug("No station, continuing");
    prev_position = next_waypoint->PositionCoordinates();
    if (context.direction == LineDirection::FORWARD) {
      ++context.index;

      if (context.index == NumberOfStations() - 1) {
        spdlog::error("Found end of line before station");
        return -1;
      }
    } else {
      --context.index;

      if (context.index == 0) {
        spdlog::error("Found end of line before station");
        return -1;
      }
    }
  }
  spdlog::error("No station found");
  return -1;
}
