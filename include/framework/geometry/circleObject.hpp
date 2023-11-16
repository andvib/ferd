#ifndef INCLUDE_FRAMEWORK_GEOMETRY_CIRCLEOBJECT_HPP_
#define INCLUDE_FRAMEWORK_GEOMETRY_CIRCLEOBJECT_HPP_

#include <GL/glew.h>

#include "framework/ferd_color.hpp"
#include "game/train_util.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"

class CircleObject {
 public:
  CircleObject();
  ~CircleObject() = default;

  CircleObject(position_t center, struct ferd_color color);

  /**
   * @brief Render the circle object
   */
  void Render(void) const;

  /**
   * @brief Calculate the Modem Matrix of the circle object
   *
   * @return glm::mat4 Model matrix
   */
  glm::mat4 CalculateModelMatrix(void) const;

 private:
  position_t m_center;
  GLuint m_vertexArrayID;
  GLuint m_vertexBuffer;
  GLfloat *m_vertex_buffer_data;
  GLuint m_colorBuffer;
  GLuint m_elementBuffer;
};

#endif /* INCLUDE_FRAMEWORK_GEOMETRY_CIRCLEOBJECT_HPP_ */
