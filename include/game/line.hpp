#ifndef INCLUDE_GAME_LINE_HPP_
#define INCLUDE_GAME_LINE_HPP_

#include <memory>
#include <vector>

#include "framework/OpenGLWrapper.hpp"
#include "framework/ferd_color.hpp"
#include "framework/geometry/lineObject.hpp"
#include "game/physics/kinematics.hpp"
#include "game/waypoint/waypoint.hpp"

enum class LineDirection { FORWARD, BACKWARD };

class Line {
 public:
  ~Line();

  Line(std::vector<Waypoint *> waypoints, struct ferd_color color,
       std::shared_ptr<OpenGLWrapper> opengl =
           std::make_shared<OpenGLWrapper>());

  /**
   * @brief Get the next station on the line
   *
   * @details Returns the position of the next station, based on the current
   *          station index.
   *
   * @param index Current station index for the train
   * @param direction The direction on the line the train is traveling
   * @return position_t Position of the next station
   */
  position_t GetNextStation(int index, LineDirection direction);

  /**
   * @brief Returns the number of stations currently in the line
   *
   * @return int The number of stations on line
   */
  int NumberOfStations() const { return v_waypoints.size(); }

  /**
   * @brief Get LineObjects representing the line
   *
   * @details Can be passed directly to World object for rendering
   *
   * @return std::vector<LineObject *> A vector with pointers to the
   * LineObjects.
   */
  std::vector<LineObject *> GetLineObjects() const { return v_line_objects; }

  /**
   * @brief Get the Waypoints on the line
   *
   * @return std::vector<LineWaypoint *>  Vector with pointers to waypoint
   *                                      objects
   */
  std::vector<Waypoint *> GetWaypoints() const { return v_waypoints; }

 private:
  std::vector<Waypoint *> v_waypoints;
  std::vector<LineObject *> v_line_objects;
  struct ferd_color m_color;
};

#endif /* INCLUDE_GAME_LINE_HPP_ */
