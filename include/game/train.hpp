#ifndef INCLUDE_GAME_TRAIN_HPP_
#define INCLUDE_GAME_TRAIN_HPP_

#include <chrono>

#include "framework/ferd_color.hpp"
#include "framework/geometry/rectangleObject.hpp"
#include "game/line.hpp"
#include "game/physics/kinematics.hpp"
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
   * @param line Line object the train will be traveling along
   * @param start_position Start position of the train
   * @param acceleration Acceleration of the train
   * @param color Color struct for the color of the train
   */
  Train(Line* line, position_t start_position, float acceleration,
        const struct ferd_color color);

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
  position_t current_station;
  int m_train_id;
};

#endif /* INCLUDE_GAME_TRAIN_HPP_ */
