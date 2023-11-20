#ifndef INCLUDE_GAME_TRAINPHYSICS_HPP_
#define INCLUDE_GAME_TRAINPHYSICS_HPP_

#include <chrono>
#include <cmath>

#include "game/train_util.hpp"

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
  position_t getPosition() { return m_pos; }

  /**
   * @brief Get the rotation object
   *
   * @return vector_t Unit vector for train rotation
   */
  vector_t getRotation() { return m_vector; }

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
  void rotateTrain(vector_t vector) { m_vector = vector; }

  /**
   * @brief Get the breaking distance of the train
   *
   * @return float Breaking distance of the train
   */
  float getBreakingDistance() const {
    return calculateBreakingDistance(
        m_acceleration,
        sqrt((m_speed.x * m_speed.x) + (m_speed.y * m_speed.y)));
  }

  /**
   * @brief Set train position to station position
   *
   * @param pos Position of station
   */
  void moveToStation(position_t pos) { m_pos = pos; }

 private:
  /**
   * @brief Calculate the breaking distance of the train
   *
   * @param acceleration Acceleration in m/s^2
   * @param speed Speed in m/s
   * @return float Breaking distance in metres
   */
  float calculateBreakingDistance(float acceleration, float speed) const;

  speed_t m_speed;
  float m_max_speed;
  float m_acceleration;
  int m_acc_direction;
  position_t m_pos;
  vector_t m_vector;
};

float calculateBreakingDistance(float acceleration, float max_speed);

#endif /* INCLUDE_GAME_TRAINPHYSICS_HPP_ */
