#ifndef INCLUDE_GAME_RAIL_STRAIGHTRAILSTATION_HPP_
#define INCLUDE_GAME_RAIL_STRAIGHTRAILSTATION_HPP_

#include "game/rail/straightRailPiece.hpp"
#include "game/waypoint/waypoint.hpp"

class StraightRailStation : public StraightRailPiece {
 public:
  StraightRailStation() = default;

  void stopPointCalculate();

  Vector2D stopPointGet() const { return m_stop_point; }

 private:
  Vector2D m_stop_point;
};

#endif /* INCLUDE_GAME_RAIL_STRAIGHTRAILSTATION_HPP_ */
