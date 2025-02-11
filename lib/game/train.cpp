#include "game/train.hpp"

#include <spdlog/spdlog.h>

#include <chrono>
#include <cstdlib>
#include <ctime>

#include "game/trainPhysics.hpp"

#define CLOCKS_PER_MSEC (CLOCKS_PER_SEC / 1000)

static const struct rectangle_points c_train_points = {
    -0.25, 0.185, -0.25, -0.185, 0.25, -0.185, 0.25, 0.185};

static get_next_train_id() {
  static int next_train_id = 1;
  return next_train_id++;
}

Train::Train(Vector2D start_position, const struct ferd_color color, std::shared_ptr<RailPiece> piece, std::shared_ptr<RailConnection> connection)
    : m_walker(), m_seeker(start_position, piece, connection), m_model_matrix() {

  m_State = STOPPED_AT_STATION;

  m_train_id = get_next_train_id();

  m_walker.set_current_rail(piece);
  m_walker.set_next_connection(connection);

  m_position = start_position;

  m_train_object = std::make_shared<RectangleObject>(c_train_points, color);
}

Train::~Train() {
}

void Train::Update(clock_t delta_time_ms) {
  float distance_travelled = 0.01 * delta_time_ms;

  m_position = m_walker.nextPositionGet(m_position, distance_travelled);
  m_vector = m_walker.rotationGet(m_position);

  m_model_matrix = CalculateModelMatrix();
  m_train_object->m_model_matrix = m_model_matrix;

  m_seeker.Update(distance_travelled, m_walker.isStationPiece());
}

glm::mat4 Train::CalculateModelMatrix() {
  float angle = glm::atan(m_vector(1) / m_vector(0));

  glm::mat4 myTranslationMatrix = glm::translate(
      glm::mat4(1.0f), glm::vec3(m_position(0), m_position(1), 0.0f));
  glm::mat4 myScalingMatrix =
      glm::scale(glm::mat4(1.0f), glm::vec3(4.3f, 4.3f, 4.3f));
  glm::mat4 myRotationMatrix =
      glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 0.0f, 1.0f));

  return myTranslationMatrix * myRotationMatrix * myScalingMatrix;
}
