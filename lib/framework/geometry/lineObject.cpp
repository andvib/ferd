#include "framework/geometry/lineObject.hpp"

#include <spdlog/spdlog.h>

static const GLfloat m_VertexBufferData[]{0, 0.5, 0, -0.5, 1, -0.5, 1, 0.5};

LineObject::LineObject() { glGenVertexArrays(1, &m_vertexArrayID); }

LineObject::LineObject(struct line points, struct line_color color) {
  glGenVertexArrays(1, &m_vertexArrayID);
  glBindVertexArray(m_vertexArrayID);

  m_points = points;

  glGenBuffers(1, &m_vertexBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(m_VertexBufferData), m_VertexBufferData,
               GL_STATIC_DRAW);

  GLuint indices[]{0, 1, 3, 2, 3, 1};

  glGenBuffers(1, &m_elementBuffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBuffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);

  GLfloat color_buffer_data[]{color.red, color.green, color.blue, color.red};

  glGenBuffers(1, &m_colorBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data,
               GL_STATIC_DRAW);

  GLfloat positionA[]{m_points.x0, m_points.y0};
  glGenBuffers(1, &m_pointa_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, m_pointa_buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(positionA), positionA, GL_STATIC_DRAW);

  GLfloat positionB[]{m_points.x1, m_points.y1};
  glGenBuffers(1, &m_pointb_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, m_pointb_buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(positionB), positionB, GL_STATIC_DRAW);

  GLfloat width[]{m_points.width};
  glGenBuffers(1, &m_width_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, m_width_buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(width), width, GL_STATIC_DRAW);
}

void LineObject::Render(void) {
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0,
                        reinterpret_cast<void*>(0));

  // pointA
  glEnableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, m_pointa_buffer);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0,
                        reinterpret_cast<void*>(0));
  glVertexAttribDivisor(1, 4);

  // pointB
  glEnableVertexAttribArray(2);
  glBindBuffer(GL_ARRAY_BUFFER, m_pointb_buffer);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0,
                        reinterpret_cast<void*>(0));
  glVertexAttribDivisor(2, 4);

  // width
  glEnableVertexAttribArray(3);
  glBindBuffer(GL_ARRAY_BUFFER, m_width_buffer);
  glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 0,
                        reinterpret_cast<void*>(0));
  glVertexAttribDivisor(3, 4);

  // Color
  glEnableVertexAttribArray(4);
  glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer);
  glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0,
                        reinterpret_cast<void*>(0));
  glVertexAttribDivisor(4, 4);

  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(2);
  glDisableVertexAttribArray(3);
  glDisableVertexAttribArray(4);
}
