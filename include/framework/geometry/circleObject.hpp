#ifndef INCLUDE_FRAMEWORK_GEOMETRY_CIRCLEOBJECT_HPP_
#define INCLUDE_FRAMEWORK_GEOMETRY_CIRCLEOBJECT_HPP_

#include <GL/glew.h>

#include <memory>

#include "framework/OpenGLWrapper.hpp"
#include "game/physics/kinematics.hpp"
#include "glm/gtc/matrix_transform.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/transform.hpp"

class CircleObject {
 public:
  explicit CircleObject(std::shared_ptr<OpenGLWrapper> opengl);
  explicit CircleObject(position_t center,
                        std::shared_ptr<OpenGLWrapper> opengl);

  ~CircleObject() = default;

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
  GLuint m_elementBuffer;
  std::shared_ptr<OpenGLWrapper> opengl_;
};

#endif /* INCLUDE_FRAMEWORK_GEOMETRY_CIRCLEOBJECT_HPP_ */
