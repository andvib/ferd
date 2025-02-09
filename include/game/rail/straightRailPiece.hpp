#ifndef INCLUDE_GAME_RAIL_STRAIGHTRAILPIECE_HPP_
#define INCLUDE_GAME_RAIL_STRAIGHTRAILPIECE_HPP_

#include "game/rail/railPiece.hpp"
#include "game/waypoint/waypoint.hpp"

class StraightRailPiece : public RailPiece {
 public:
  StraightRailPiece() = default;

  Vector2D PositionOnRailGet(Vector2D current_position, float distance_travelled,
                             RailDirection direction) override;
  Vector2D OrientationOnRailGet(Vector2D position_on_rail, RailDirection direcion) override;
};

#endif /* INCLUDE_GAME_RAIL_STRAIGHTRAILPIECE_HPP_   */
