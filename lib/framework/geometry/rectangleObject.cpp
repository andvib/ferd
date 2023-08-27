#include "framework/geometry/rectangleObject.hpp"

#include <spdlog/spdlog.h>

#include <glm/gtc/type_ptr.hpp>

RectangleObject::RectangleObject() { glGenVertexArrays(1, &m_vertexArrayID); }

RectangleObject::RectangleObject(struct rectangle_points rectangle_p,
                                 struct rectangle_color color) {
  glGenVertexArrays(1, &m_vertexArrayID);
  glBindVertexArray(m_vertexArrayID);

  m_points = rectangle_p;

  GLfloat m_VertexBufferData[]{m_points.x0, m_points.y0, m_points.x1,
                               m_points.y1, m_points.x2, m_points.y2,
                               m_points.x3, m_points.y3};

  glGenBuffers(1, &m_vertexBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(m_VertexBufferData), m_VertexBufferData,
               GL_STATIC_DRAW);

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
