#ifndef INCLUDE_FRAMEWORK_GEOMETRY_RECTANGLEOBJECT_HPP_
#define INCLUDE_FRAMEWORK_GEOMETRY_RECTANGLEOBJECT_HPP_

#include <GL/glew.h>

#include <chrono>

#include "framework/ferd_color.hpp"
#include "glm/gtc/matrix_transform.hpp"

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
  RectangleObject(struct rectangle_points rectangle_p, struct ferd_color color);

  /**
   * @brief Update attributes of the rectangle object
   *
   * @details Updates the position and calculates the model matrix
   */
  //virtual void Update(clock_t delta_time) = 0;

  /**
   * @brief Render the rectangle object
   */
  void Render(void);

  /**
   * @brief Calculate the Model Matrix object
   *
   * @return glm::mat4 Model Matrix
   */
  //virtual glm::mat4 CalculateModelMatrix() = 0;

  glm::mat4 m_model_matrix;

 private:
  struct rectangle_points m_points;
  struct ferd_color m_color;
  GLuint m_vertexArrayID;
  GLuint m_vertexBuffer;
  GLfloat *m_vertex_buffer_data;
  GLuint m_colorBuffer;
  GLuint m_elementBuffer;
};

#endif /* INCLUDE_FRAMEWORK_GEOMETRY_RECTANGLEOBJECT_HPP_ */
