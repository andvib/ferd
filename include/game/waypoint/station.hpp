#ifndef INCLUDE_GAME_WAYPOINT_STATION_HPP_
#define INCLUDE_GAME_WAYPOINT_STATION_HPP_

#include <iostream>

#include "framework/geometry/circleObject.hpp"
#include "game/waypoint/waypoint.hpp"

class Station : public Waypoint, public CircleObject {
 public:
  Station();
  explicit Station(position_t coordinates)
      : Waypoint(coordinates), CircleObject(coordinates) {}
};

#endif /* INCLUDE_GAME_WAYPOINT_STATION_HPP_ */
