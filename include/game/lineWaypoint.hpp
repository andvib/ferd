#ifndef INCLUDE_GAME_LINEWAYPOINT_HPP_
#define INCLUDE_GAME_LINEWAYPOINT_HPP_

#include "framework/ferd_color.hpp"
#include "framework/geometry/circleObject.hpp"
#include "game/train_util.hpp"

class LineWaypoint : public CircleObject {
 public:
  LineWaypoint();
  explicit LineWaypoint(position_t coordinates, const struct ferd_color color)
      : CircleObject(coordinates, color),
        m_position(coordinates),
        m_is_station(false) {}

  LineWaypoint(position_t coordinates, const struct ferd_color color,
               bool is_station)
      : CircleObject(coordinates, color),
        m_position(coordinates),
        m_is_station(is_station) {}

  /**
   * @brief Return the coordinates of the LineWaypoint
   *
   * @return position_t The position of the LineWaypoint
   */
  position_t PositionCoordinates() const { return m_position; }

  /**
   * @brief Check if waypoint is a station
   *
   * @return  true  Waypoint is a station
   * @return  false Waypoint is not a station
   */
  bool IsStation() const { return m_is_station; }

 private:
  position_t m_position;
  bool m_is_station;
};

#endif /* INCLUDE_GAME_LINEWAYPOINT_HPP_ */
