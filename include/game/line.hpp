#ifndef INCLUDE_GAME_LINE_HPP_
#define INCLUDE_GAME_LINE_HPP_

#include <vector>

#include "framework/geometry/lineObject.hpp"
#include "game/lineWaypoint.hpp"
#include "game/train_util.hpp"

enum class LineDirection { FORWARD, BACKWARD };

class Line {
 public:
  Line() = default;
  ~Line() = default;

  Line(std::vector<LineWaypoint *> waypoints, struct line_color color);

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

 private:
  std::vector<LineWaypoint *> v_waypoints;
  std::vector<LineObject *> v_line_objects;
  struct line_color m_color;
};

#endif /* INCLUDE_GAME_LINE_HPP_ */
