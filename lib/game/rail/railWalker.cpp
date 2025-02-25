#include "game/rail/railWalker.hpp"

#include <spdlog/spdlog.h>

#include "game/physics/kinematics.hpp"
#include "game/rail/railPiece.hpp"

Vector2D RailWalker::moveToNextRail() {
  if (m_direction == RailDirection::RAIL_DIRECTION_A_TO_B) {
    bool change_dir;

    std::tie(connection, change_dir) = connection->getConnectionB();
    std::tie(current_rail, change_dir) = connection->getRailB();

    if (change_dir) {
      m_direction = RailDirection::RAIL_DIRECTION_B_TO_A;
      std::tie(current_rail, change_dir) = connection->getRailA();
    }
  } else {
    bool change_dir;
    std::tie(connection, change_dir) = connection->getConnectionA();
    std::tie(current_rail, change_dir) = connection->getRailA();

    if (change_dir) {
      m_direction = RailDirection::RAIL_DIRECTION_A_TO_B;

      std::tie(current_rail, change_dir) = connection->getRailB();
    }
  }

  return connection->getPos();
}

Vector2D RailWalker::nextPositionGet(Vector2D current_position,
                                     float distance_travelled) {
  Vector2D new_position = current_rail->PositionOnRailGet(
      current_position, distance_travelled, m_direction);

  if ((m_skip_frame_counter == 0) &&
      (!current_rail->IsPointOnPiece(new_position))) {
    if (m_skip_frame_counter != 0) {
      return new_position;
    }

    current_position = moveToNextRail();
    new_position = current_rail->PositionOnRailGet(
        current_position, distance_travelled, m_direction);
    m_skip_frame_counter = 10;
  }

  if (m_skip_frame_counter > 0) {
    m_skip_frame_counter--;
  }

  return new_position;
}

Vector2D RailWalker::rotationGet(Vector2D current_position) {
  return current_rail->OrientationOnRailGet(current_position, m_direction);
}

Vector2D RailWalker::stationPosition() {
  auto station_ptr =
      std::dynamic_pointer_cast<StraightRailStation>(current_rail);
  if (station_ptr) {
    return station_ptr->stopPointGet();
  } else {
    return Vector2D(0, 0);
  }
}
