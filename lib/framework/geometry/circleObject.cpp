#include "framework/geometry/circleObject.hpp"

#include <spdlog/spdlog.h>

CircleObject::CircleObject() { glGenVertexArrays(1, &m_vertexArrayID); }

CircleObject::CircleObject(position_t center) : m_center(center) {
  glGenVertexArrays(1, &m_vertexArrayID);
  glBindVertexArray(m_vertexArrayID);

  std::array<GLfloat, 8> circle_square_points = {-0.5, 0.5,  -0.5, -0.5,
                                                 0.5,  -0.5, 0.5,  0.5};

  glGenBuffers(1, &m_vertexBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(circle_square_points),
               circle_square_points.data(), GL_STATIC_DRAW);

  std::array<GLuint, 6> indices = {0, 1, 3, 2, 3, 1};

  glGenBuffers(1, &m_elementBuffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBuffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(),
               GL_STATIC_DRAW);

  spdlog::info("CircleObject created!");
}

void CircleObject::Render(void) const {
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0,
                        reinterpret_cast<void*>(0));

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBuffer);

  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
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
