#ifndef INCLUDE_GAME_LINE_HPP_
#define INCLUDE_GAME_LINE_HPP_

#include <memory>
#include <vector>

#include "framework/OpenGLWrapper.hpp"
#include "framework/ferd_color.hpp"
#include "framework/geometry/lineObject.hpp"
#include "game/physics/kinematics.hpp"
#include "game/waypoint/station.hpp"
#include "game/waypoint/waypoint.hpp"

enum class LineDirection { FORWARD, BACKWARD };

struct line_ctx {
  int index;
  LineDirection direction;
};

class Line {
 public:
  ~Line() = default;

  Line(std::vector<Waypoint *> waypoints, struct ferd_color color,
       std::shared_ptr<OpenGLWrapper> opengl =
           std::make_shared<OpenGLWrapper>());

  /**
   * @brief Get position of the next waypoint
   *
   * @param context       Line context
   * @return position_t   Position of the next waypoing
   */
  int GetNextWaypoint(position_t *waypoint_pos, line_ctx ctx);

  /**
   * @brief Get the distance to the next waypoint
   *
   * @param context           Line context
   * @param current_position  Current positing
   * @return float              Distance to the next waypoint
   */
  float GetNextWaypointDistance(line_ctx context, position_t current_position);

  /**
   * @brief Get the next station on the line
   *
   * @details Finds the position of the next station based on the current
   *          waypoint index.
   * @param waypoint_pos  Pointer to variable to store location of next station
   * @param context       Line context
   *
   * @return int          0 on success, negative value otherwise
   */
  int GetNextStation(position_t *waypoint_pos, line_ctx ctx);

  /**
   * @brief Get the distance to the next station on the line
   *
   * @param context           Line context
   * @param current_position  Current position
   * @return float              Distance to next station
   */
  float GetNextStationDistance(line_ctx context, position_t current_position);

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
  std::vector<std::shared_ptr<LineObject>> GetLineObjects() const {
    return v_line_objects;
  }

  /**
   * @brief Get the Waypoints on the line
   *
   * @return std::vector<LineWaypoint *>  Vector with pointers to waypoint
   *                                      objects
   */
  std::vector<Waypoint *> GetWaypoints() const { return v_waypoints; }

 private:
  std::vector<Waypoint *> v_waypoints;
  std::vector<std::shared_ptr<LineObject>> v_line_objects;
  struct ferd_color m_color;
};

#endif /* INCLUDE_GAME_LINE_HPP_ */
