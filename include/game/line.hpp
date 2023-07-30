#ifndef INCLUDE_GAME_LINE_HPP_
#define INCLUDE_GAME_LINE_HPP_

#include <vector>

#include "game/train_util.hpp"

enum class LineDirection { FORWARD, BACKWARD };

class LineWaypoint {
 public:
  LineWaypoint();
  LineWaypoint(position_t coordinates, bool is_station) {
    m_position = coordinates;
  }

  /**
   * @brief Return the coordinates of the LineWaypoint
   *
   * @return position_t The position of the LineWaypoint
   */
  position_t PositionCoordinates() { return m_position; }

 private:
  position_t m_position;
};

class Line {
 public:
  Line() {}
  ~Line() {}

  explicit Line(std::vector<LineWaypoint *> waypoints);

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
  int NumberOfStations() { return v_waypoints.size(); }

 private:
  std::vector<LineWaypoint *> v_waypoints;
};

#endif /* INCLUDE_GAME_LINE_HPP_ */
