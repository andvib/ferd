#ifndef INCLUDE_GAME_TRAIN_HPP_
#define INCLUDE_GAME_TRAIN_HPP_

#include <chrono>

#include "game/rectangleObject.hpp"
#include "game/trainNavigator.hpp"
#include "game/trainPhysics.hpp"

enum train_state { STOPPED_AT_STATION, ENROUTE, APPROACH };

class Train : public RectangleObject {
 public:
  Train();
  ~Train();

  /**
   * @brief Construct a new Train object
   *
   * @param x Start position
   * @param y End position
   * @param color Color struct for color of the train
   */
  Train(position_t start, position_t end, const struct rectangle_color color);

  /**
   * @brief Construct a new Train object
   *
   * @param x Start position
   * @param y End position
   * @param acceleration Acceleration of the train
   * @param color Color struct for color of the train
   */
  Train(position_t start, position_t end, float acceleration,
        const struct rectangle_color color);

  /**
   * @brief Update the state machine and physics model of the train, and
   * navigate the route
   *
   * @param delta_time_ms Time since previous update, in milliseconds
   */
  void Update(clock_t delta_time_ms) override;

  /**
   * @brief Calculate the model matrix for the train
   *
   * @return glm::mat4 Model matrix
   */
  glm::mat4 CalculateModelMatrix() override;

 private:
  TrainNavigator* p_Route;
  TrainPhysics* p_Physics;
  train_state m_State;
  clock_t m_duration_at_station = 0;
  int m_wait_time = 0;
};

#endif /* INCLUDE_GAME_TRAIN_HPP_ */
