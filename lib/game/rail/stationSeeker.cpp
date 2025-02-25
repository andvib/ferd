#include "game/rail/stationSeeker.hpp"

static const struct rectangle_points c_train_points = {
    -0.25, 0.185, -0.25, -0.185, 0.25, -0.185, 0.25, 0.185};

StationSeeker::StationSeeker(Vector2D start_position, std::shared_ptr<RailPiece> piece, std::shared_ptr<RailConnection> connection) : m_seeker_position(start_position) {
  set_current_rail(piece);
  set_next_connection(connection);
  
  m_seeker_object = std::make_shared<RectangleObject>(c_train_points, FERD_COLOR_3);
}

void StationSeeker::Update(float distance_travelled, bool train_at_station) {
  switch(m_state) {
    case MOVING:
      if (isStationPiece()) {
        m_seeker_position = stationPosition();
        m_state = AT_STATION;
      } else {
        m_seeker_position = nextPositionGet(m_seeker_position, distance_travelled * 1.2);
      }
    
      m_seeker_matrix = CalculateSeekerMatrix();
      m_seeker_object->m_model_matrix = m_seeker_matrix;
      break;
  
    case AT_STATION:
      if(train_at_station) {
        m_state = MOVING;
        m_seeker_position = moveToNextRail();
      }
      break;
  }
}

glm::mat4 StationSeeker::CalculateSeekerMatrix() {
  float angle = 1.0;
  
  glm::mat4 myTranslationMatrix = glm::translate(
    glm::mat4(1.0f), glm::vec3(m_seeker_position(0), m_seeker_position(1), 0.0f));
  glm::mat4 myScalingMatrix =
    glm::scale(glm::mat4(1.0f), glm::vec3(4.3f, 4.3f, 4.3f));
  glm::mat4 myRotationMatrix =
    glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 0.0f, 1.0f));
  
  return myTranslationMatrix * myRotationMatrix * myScalingMatrix;
}
