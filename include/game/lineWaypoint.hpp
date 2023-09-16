#ifndef INCLUDE_GAME_LINEWAYPOINT_HPP_
#define INCLUDE_GAME_LINEWAYPOINT_HPP_

#include "game/train_util.hpp"

class LineWaypoint {
 public:
  LineWaypoint();
  explicit LineWaypoint(position_t coordinates) : m_position(coordinates) {}

  /**
   * @brief Return the coordinates of the LineWaypoint
   *
   * @return position_t The position of the LineWaypoint
   */
  position_t PositionCoordinates() const { return m_position; }

 private:
  position_t m_position;
};

#endif /* INCLUDE_GAME_LINEWAYPOINT_HPP_ */
