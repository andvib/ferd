#ifndef INCLUDE_GAME_WAYPOINT_WAYPOINT_HPP_
#define INCLUDE_GAME_WAYPOINT_WAYPOINT_HPP_

#include <iostream>

#include "game/physics/kinematics.hpp"

class Waypoint {
 public:
  Waypoint();
  explicit Waypoint(position_t coordinates) : m_position(coordinates) {}

  /* This is done as a virtual function to achieve polymorphism */
  virtual position_t PositionCoordinates() const { return m_position; }

  Vector2D PositionVector() const { return Vector2D(m_position.x, m_position.y); }

 private:
  position_t m_position;
};

#endif /* INCLUDE_GAME_WAYPOINT_WAYPOINT_HPP_ */
