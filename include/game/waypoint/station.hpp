#ifndef INCLUDE_GAME_WAYPOINT_STATION_HPP_
#define INCLUDE_GAME_WAYPOINT_STATION_HPP_

#include <iostream>
#include <memory>

#include "framework/OpenGLWrapper.hpp"
#include "framework/geometry/circleObject.hpp"
#include "game/waypoint/waypoint.hpp"

class Station : public Waypoint, public CircleObject {
 public:
  explicit Station(
      position_t coordinates,
      std::shared_ptr<OpenGLWrapper> opengl = std::make_shared<OpenGLWrapper>())
      : Waypoint(coordinates), CircleObject(coordinates, opengl) {}

  int getID() const { return m_station_id; }

 private:
  static int getNextID() {
    static int nextID = 0;
    return nextID++;
  }

  int m_station_id = getNextID();
};

#endif /* INCLUDE_GAME_WAYPOINT_STATION_HPP_ */
