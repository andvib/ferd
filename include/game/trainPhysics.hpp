#ifndef INCLUDE_GAME_TRAINPHYSICS_HPP_
#define INCLUDE_GAME_TRAINPHYSICS_HPP_

#include <chrono>
#include <cmath>

#include "game/physics/kinematics.hpp"

class TrainPhysics {
 public:
  TrainPhysics();

  /**
   * @brief Construct a new Train Physics object
   *
   * @param start_pos Initial position of the train
   * @param acceleration Acceleration of the train
   */
  TrainPhysics(position_t start_pos, float acceleration);

  /**
   * @brief Update the physics attributes
   *
   * @param delta_time_ms
   */
  void Update(clock_t delta_time_ms);

  /**
   * @brief Get the Position object
   *
   * @return position_t Current position of the train
   */
  position_t getPosition() { return {m_pos(0), m_pos(1)}; }

  /**
   * @brief Get the rotation object
   *
   * @return vector_t Unit vector for train rotation
   */
  vector_t getRotation() { return {m_vector(0), m_vector(1)}; }

  /**
   * @brief Stop the train (sets speed to 0)
   */
  void stop();

  /**
   * @brief Accelerate the train
   */
  void accelerate() { m_acc_direction = 1; }

  /**
   * @brief Decelerate the train
   */
  void decelerate() { m_acc_direction = -1; }

  /**
   * @brief Rotate the train according to the given unit vector
   *
   * @param vector Unit vector train rotation should follow
   */
  void rotateTrain(vector_t vector) {
    m_vector(0) = vector.x;
    m_vector(1) = vector.y;
  }

  /**
   * @brief Get the breaking distance of the train
   *
   * @return float Breaking distance of the train
   */
  float getBreakingDistance() const {
    return calculateBreakingDistance(m_acceleration, absoluteSpeed(m_speed));
  }

  /**
   * @brief Set train position to station position
   *
   * @param pos Position of station
   */
  void moveToStation(position_t pos) {
    m_pos(0) = pos.x;
    m_pos(1) = pos.y;
  }

 private:
  /**
   * @brief Calculate the breaking distance of the train
   *
   * @param acceleration Acceleration in m/s^2
   * @param speed Speed in m/s
   * @return float Breaking distance in metres
   */
  float calculateBreakingDistance(float acceleration, float speed) const;

  float m_max_speed;
  float m_acceleration;
  int m_acc_direction;
  Vector2D m_pos;
  Vector2D m_speed{0, 0};
  Vector2D m_vector{1, 0};
};
float calculateBreakingDistance(float acceleration, float max_speed);

#endif /* INCLUDE_GAME_TRAINPHYSICS_HPP_ */
