#include "framework/geometry/rectangleObject.hpp"

#include <spdlog/spdlog.h>

#include <glm/gtc/type_ptr.hpp>

static const std::array<GLfloat, 8> c_train_points = {
  -0.25, 0.185, -0.25, -0.185, 0.25, -0.185, 0.25, 0.185};

RectangleObject::RectangleObject() { glGenVertexArrays(1, &m_vertexArrayID); }

RectangleObject::RectangleObject(struct ferd_color color) {
  glGenVertexArrays(1, &m_vertexArrayID);
  glBindVertexArray(m_vertexArrayID);

  glGenBuffers(1, &m_vertexBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(c_train_points),
               static_cast<const void*>(c_train_points.data()), GL_STATIC_DRAW);

  GLuint indices[]{0, 1, 3, 2, 3, 1};

  glGenBuffers(1, &m_elementBuffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBuffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);

  GLfloat color_buffer_data[]{color.red, color.green, color.blue};

  glGenBuffers(1, &m_colorBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data,
               GL_STATIC_DRAW);

  spdlog::info("Object created!");
}

void RectangleObject::Render(void) {
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0,
                        reinterpret_cast<void*>(0));

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBuffer);

  glEnableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0,
                        reinterpret_cast<void*>(0));
  glVertexAttribDivisor(1, 4);

  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
}

void RectangleObject::objectLocationSet(Vector2D position, Vector2D orientation) {
  m_object_position = position;
  m_object_orientation = orientation;
}

glm::mat4 RectangleObject::CalculateModelMatrix() {
  float angle = glm::atan(m_object_orientation(1) / m_object_orientation(0));

  glm::mat4 myTranslationMatrix = glm::translate(
      glm::mat4(1.0f), glm::vec3(m_object_position(0), m_object_position(1), 0.0f));
  glm::mat4 myScalingMatrix =
      glm::scale(glm::mat4(1.0f), glm::vec3(4.3f, 4.3f, 4.3f));
  glm::mat4 myRotationMatrix =
      glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 0.0f, 1.0f));

  return myTranslationMatrix * myRotationMatrix * myScalingMatrix;
}
