#include "game/train.hpp"

#include <spdlog/spdlog.h>

#include <chrono>
#include <cstdlib>
#include <ctime>

#include "game/trainPhysics.hpp"

#define CLOCKS_PER_MSEC (CLOCKS_PER_SEC / 1000)

static const struct rectangle_points c_train_points = {
    -0.25, 0.185, -0.25, -0.185, 0.25, -0.185, 0.25, 0.185};

Train::Train() : RectangleObject(c_train_points, FERD_COLOR_1) {
  p_Route = new TrainNavigator();
  p_Physics = new TrainPhysics();
}

Train::~Train() {
  delete p_Route;
  delete p_Physics;
}

Train::Train(Line* line, position_t start_position, float acceleration,
             const struct ferd_color color)
    : RectangleObject(c_train_points, color) {
  p_Physics = new TrainPhysics(start_position, acceleration);
  p_Route = new TrainNavigator(line);

  p_Physics->rotateTrain(
      p_Route->vectorToNextStation(p_Physics->getPosition()));
  m_State = STOPPED_AT_STATION;
}

Train::Train(Line* line, unsigned int start_station, position_t start_position,
             float acceleration, const struct ferd_color color)
    : RectangleObject(c_train_points, color) {
  p_Physics = new TrainPhysics(start_position, acceleration);
  p_Route = new TrainNavigator(line, start_station);

  p_Physics->rotateTrain(
      p_Route->vectorToNextStation(p_Physics->getPosition()));
  m_State = STOPPED_AT_STATION;
}

void Train::Update(clock_t delta_time_ms) {
  switch (m_State) {
    case STOPPED_AT_STATION:
      if (m_duration_at_station == 0) {
        m_duration_at_station = clock();
        m_wait_time = rand() / (RAND_MAX / 3000);
        current_station = p_Route->nextStationPos();
      }

      if (((clock() - m_duration_at_station) / CLOCKS_PER_MSEC) > m_wait_time) {
        m_State = ENROUTE;
        vector_t vector_next =
            p_Route->vectorToNextStation(p_Physics->getPosition());
        p_Physics->rotateTrain({vector_next});
        p_Physics->accelerate();
        m_duration_at_station = 0;
      }
      break;

    case ENROUTE:
      p_Physics->Update(delta_time_ms);

      if (p_Route->distanceToStation(p_Physics->getPosition()) <
          p_Physics->getBreakingDistance()) {
        spdlog::info("Approaching station!");
        p_Physics->decelerate();
        m_State = APPROACH;
      }
      break;

    case APPROACH:
      p_Physics->Update(delta_time_ms);

      if (p_Route->atStation(p_Physics->getPosition())) {
        p_Physics->stop();
        p_Physics->moveToStation(current_station);
        m_State = STOPPED_AT_STATION;
      }
      break;
  }
}

glm::mat4 Train::CalculateModelMatrix() {
  position_t current_position = p_Physics->getPosition();
  vector_t vector_next = p_Physics->getRotation();
  float angle = glm::atan(vector_next.y / vector_next.x);

  glm::mat4 myTranslationMatrix = glm::translate(
      glm::mat4(1.0f), glm::vec3(current_position.x, current_position.y, 0.0f));
  glm::mat4 myScalingMatrix =
      glm::scale(glm::mat4(1.0f), glm::vec3(0.75f, 0.75f, 0.75f));
  glm::mat4 myRotationMatrix =
      glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 0.0f, 1.0f));

  return myTranslationMatrix * myRotationMatrix * myScalingMatrix;
}
