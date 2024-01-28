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

  int getID() const { return m_station_id; }

 private:
  static int getNextID() {
    static int nextID = 0;
    return nextID++;
  }

  int m_station_id = getNextID();
};

#endif /* INCLUDE_GAME_WAYPOINT_STATION_HPP_ */
