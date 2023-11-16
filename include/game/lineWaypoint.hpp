#ifndef INCLUDE_GAME_LINEWAYPOINT_HPP_
#define INCLUDE_GAME_LINEWAYPOINT_HPP_

#include "framework/ferd_color.hpp"
#include "framework/geometry/circleObject.hpp"
#include "game/train_util.hpp"

class LineWaypoint : public CircleObject {
 public:
  LineWaypoint();
  explicit LineWaypoint(position_t coordinates, const struct ferd_color color)
      : CircleObject(coordinates, color), m_position(coordinates) {}

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
