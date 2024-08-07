#ifndef INCLUDE_GAME_TRAINNAVIGATOR_HPP_
#define INCLUDE_GAME_TRAINNAVIGATOR_HPP_
#include <vector>

#include "game/line.hpp"
#include "game/physics/kinematics.hpp"

class TrainNavigator {
 public:
  TrainNavigator();

  /**
   * @brief Construct a new Train Navigator object
   *
   * @param line Line that the train will be traveling
   */
  explicit TrainNavigator(Line *line);

  /**
   * @brief Check if train is currently at the next station on the line
   *
   * @param current_position Current position of the train
   * @return true Train is at station
   * @return false Train is not at station
   */
  bool atStation(position_t current_position);

  /**
   * @brief Check if train is currently at the next waypoint on the line
   *
   * @param current_position  Current position of the train
   *
   * @return  true  Train is at waypoint
   * @return  false Train is not at waypoint
   */
  bool atWaypoint(position_t current_position);

  /**
   * @brief Get the vector to next waypoint on the line
   *
   * @details Calculates the unit vector from the previous to the next station
   *
   * @return vector_t Unit vector from the previous to the next station
   */
  vector_t vectorToNextWaypoint(position_t current_position);

  /**
   * @brief Get the distance to the next station based on the current position
   *
   * @param current_position Current position of the train
   * @return float Distance to station from the current position
   */
  float distanceToStation(position_t current_position);

  /**
   * @brief Get position of next waypoint on the line
   *
   * @return position_t Position of next station
   */
  position_t nextWaypointPos();

 private:
  void updateLineContext();
  Line *p_line;
  line_ctx m_line_context;
};

#endif /* INCLUDE_GAME_TRAINNAVIGATOR_HPP_ */
