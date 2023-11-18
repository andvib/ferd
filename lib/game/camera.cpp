#include "game/camera.hpp"

#include "spdlog/spdlog.h"

glm::mat4 Camera::calculateViewProjMatrix() {
  glm::mat4 View = glm::lookAt(
      glm::vec3(Position.x, Position.y, 5),  // Position of camera
      glm::vec3(Position.x, Position.y, 0),  // Point camera looks at
      glm::vec3(0, 1, 0));                   // Up vector
  glm::mat4 Projection = glm::ortho(
      Dimensions.left * ZoomLevel, Dimensions.right * ZoomLevel,
      Dimensions.bottom * ZoomLevel, Dimensions.top * ZoomLevel, 0.0f, 100.0f);

  return Projection * View;
}
