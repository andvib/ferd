#ifndef INCLUDE_GAME_RAIL_RAILPIECE_HPP_
#define INCLUDE_GAME_RAIL_RAILPIECE_HPP_

#include <string>

#include "framework/geometry/lineObject.hpp"
#include "game/physics/kinematics.hpp"
#include "game/waypoint/waypoint.hpp"

enum class RailDirection {RAIL_DIRECTION_A_TO_B, RAIL_DIRECTION_B_TO_A};

class RailPiece {
 public:
  RailPiece() = default;

  int waypointsSet(Waypoint *wp_a, Waypoint *wp_b);

  float TotalLengthGet() const { return m_total_length; }

  bool IsPointOnPiece(Vector2D point) const;

  virtual Vector2D PositionOnRailGet(Vector2D current_position,
                                     float distance_travelled,
                                     RailDirection direction) = 0;

  virtual Vector2D OrientationOnRailGet(Vector2D position_on_rail, RailDirection direction) = 0;

  Waypoint *m_wp_a;
  Waypoint *m_wp_b;
  float m_total_length;
  std::string name;
};

#endif /* INCLUDE_GAME_RAIL_RAILPIECE_HPP_ */
