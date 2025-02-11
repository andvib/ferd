#include "framework/geometry/circleObject.hpp"

#include <spdlog/spdlog.h>

#include <memory>

CircleObject::CircleObject(std::shared_ptr<OpenGLWrapper> opengl)
    : opengl_(opengl) {
  opengl_->glGenVertexArrays(1, &m_vertexArrayID);
}

CircleObject::CircleObject(position_t center,
                           std::shared_ptr<OpenGLWrapper> opengl)
    : m_center(center), opengl_(opengl) {
  opengl_->glGenVertexArrays(1, &m_vertexArrayID);
  opengl_->glBindVertexArray(m_vertexArrayID);

  spdlog::error("Center is {}, {}", center.x, center.y);

  std::array<GLfloat, 8> circle_square_points = {-0.5, 0.5,  -0.5, -0.5,
                                                 0.5,  -0.5, 0.5,  0.5};

  opengl_->glGenBuffers(1, &m_vertexBuffer);
  opengl_->glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
  opengl_->glBufferData(GL_ARRAY_BUFFER, sizeof(circle_square_points),
                        circle_square_points.data(), GL_STATIC_DRAW);

  std::array<GLuint, 6> indices = {0, 1, 3, 2, 3, 1};

  opengl_->glGenBuffers(1, &m_elementBuffer);
  opengl_->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBuffer);
  opengl_->glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices),
                        indices.data(), GL_STATIC_DRAW);

  spdlog::info("CircleObject created!");
}

void CircleObject::Render(void) const {
  opengl_->glEnableVertexAttribArray(0);
  opengl_->glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
  opengl_->glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0,
                                 reinterpret_cast<void*>(0));

  opengl_->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBuffer);

  opengl_->glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
  opengl_->glDisableVertexAttribArray(0);
  opengl_->glDisableVertexAttribArray(1);
}

glm::mat4 CircleObject::CalculateModelMatrix() const {
  glm::mat4 myTranslationMatrix =
      glm::translate(glm::mat4(1.0f), glm::vec3(m_center.x, m_center.y, 0.0f));
  glm::mat4 myScalingMatrix =
      glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 2.0f, 2.0f));
  glm::mat4 myRotationMatrix =
      glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0.0f, 0.0f, 1.0f));

  return myTranslationMatrix * myRotationMatrix * myScalingMatrix;
}
