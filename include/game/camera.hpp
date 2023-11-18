#ifndef INCLUDE_GAME_CAMERA_HPP_
#define INCLUDE_GAME_CAMERA_HPP_

#include <glm/gtc/matrix_transform.hpp>

#include "spdlog/spdlog.h"

struct cameraPos {
  double x, y;
};

struct cameraDimensions {
  float left, right, bottom, top;
};

class Camera {
 private:
  cameraPos Position = {0, 0};
  cameraDimensions Dimensions = {-10.0f, 10.0f, -10.0f, 10.0f};
  const float Speed = 0.2;
  float ZoomLevel = 1.0;
  const float ZoomSpeed = 0.03;

 public:
  /**
   * @brief Construct a new Camera object
   *
   * @details Initializes the camera at the origin
   */
  Camera() = default;

  /**
   * @brief Return the VP matrix
   *
   * @details Calculates the view-projection (VP) matrix associated with the
   * camera.
   *
   * @return glm::mat4 The VP matrix
   */
  glm::mat4 calculateViewProjMatrix();

  /**
   * @brief Move the camera
   *
   * @details The move functions can be used to move the camera one unit.
   */
  void moveUp() { Position.y += Speed; }
  void moveDown() { Position.y -= Speed; }
  void moveLeft() { Position.x -= Speed; }
  void moveRight() { Position.x += Speed; }

  /**
   * @brief Zoom the camera
   *
   * @details Update the zoom level of the camera
   */
  void zoomIn() { ZoomLevel -= ZoomSpeed; }
  void zoomOut() { ZoomLevel += ZoomSpeed; }
};

#endif /* INCLUDE_GAME_CAMERA_HPP_ */
