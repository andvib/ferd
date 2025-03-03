#ifndef INCLUDE_FRAMEWORK_GEOMETRY_RECTANGLEOBJECT_HPP_
#define INCLUDE_FRAMEWORK_GEOMETRY_RECTANGLEOBJECT_HPP_

#include <GL/glew.h>

#include <chrono>

#include "framework/ferd_color.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "game/physics/kinematics.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/transform.hpp"

struct rectangle_points {
  GLfloat x0, y0;
  GLfloat x1, y1;
  GLfloat x2, y2;
  GLfloat x3, y3;
};

class RectangleObject {
 public:
  RectangleObject();
  explicit RectangleObject(struct ferd_color color);

  /**
   * @brief Render the rectangle object
   */
  void Render(void);

  /**
   * @brief Set the position and vector of object
   *
   * @param position  New position of the object
   * @param vector    New orientation of the object
   */
  void objectLocationSet(Vector2D position, Vector2D orientation);

  /**
   * @brief Calculate the Model Matrix object
   *
   * @return glm::mat4 Model Matrix
   */
  glm::mat4 CalculateModelMatrix();

 private:
  struct rectangle_points m_points;
  struct ferd_color m_color;
  Vector2D m_object_position;
  Vector2D m_object_orientation;
  GLuint m_vertexArrayID;
  GLuint m_vertexBuffer;
  GLfloat *m_vertex_buffer_data;
  GLuint m_colorBuffer;
  GLuint m_elementBuffer;
};

#endif /* INCLUDE_FRAMEWORK_GEOMETRY_RECTANGLEOBJECT_HPP_ */
