#include "framework/geometry/lineObject.hpp"

#include <spdlog/spdlog.h>

#include <memory>

static const GLfloat m_VertexBufferData[]{0, 0.5, 0, -0.5, 1, -0.5, 1, 0.5};

LineObject::LineObject(std::shared_ptr<OpenGLWrapper> opengl)
    : opengl_(opengl) {
  glGenVertexArrays(1, &m_vertexArrayID);
}

LineObject::LineObject(struct line points, struct ferd_color color,
                       std::shared_ptr<OpenGLWrapper> opengl)
    : m_points(points), opengl_(opengl) {
  opengl_->glGenVertexArrays(1, &m_vertexArrayID);
  opengl_->glBindVertexArray(m_vertexArrayID);
  opengl_->glGenBuffers(1, &m_vertexBuffer);
  opengl_->glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
  opengl_->glBufferData(GL_ARRAY_BUFFER, sizeof(m_VertexBufferData),
                        m_VertexBufferData, GL_STATIC_DRAW);

  GLuint indices[]{0, 1, 3, 2, 3, 1};

  opengl_->glGenBuffers(1, &m_elementBuffer);
  opengl_->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBuffer);
  opengl_->glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
                        GL_STATIC_DRAW);
  GLfloat color_buffer_data[]{color.red, color.green, color.blue};

  opengl_->glGenBuffers(1, &m_colorBuffer);
  opengl_->glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer);
  opengl_->glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data),
                        color_buffer_data, GL_STATIC_DRAW);
  GLfloat positionA[]{m_points.x0, m_points.y0};
  opengl_->glGenBuffers(1, &m_pointa_buffer);
  opengl_->glBindBuffer(GL_ARRAY_BUFFER, m_pointa_buffer);
  opengl_->glBufferData(GL_ARRAY_BUFFER, sizeof(positionA), positionA,
                        GL_STATIC_DRAW);

  GLfloat positionB[]{m_points.x1, m_points.y1};
  opengl_->glGenBuffers(1, &m_pointb_buffer);
  opengl_->glBindBuffer(GL_ARRAY_BUFFER, m_pointb_buffer);
  opengl_->glBufferData(GL_ARRAY_BUFFER, sizeof(positionB), positionB,
                        GL_STATIC_DRAW);

  GLfloat width[]{m_points.width};
  opengl_->glGenBuffers(1, &m_width_buffer);
  opengl_->glBindBuffer(GL_ARRAY_BUFFER, m_width_buffer);
  opengl_->glBufferData(GL_ARRAY_BUFFER, sizeof(width), width, GL_STATIC_DRAW);
}

void LineObject::Render(void) const {
  opengl_->glEnableVertexAttribArray(0);
  opengl_->glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
  opengl_->glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

  // pointA
  opengl_->glEnableVertexAttribArray(1);
  opengl_->glBindBuffer(GL_ARRAY_BUFFER, m_pointa_buffer);
  opengl_->glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
  opengl_->glVertexAttribDivisor(1, 4);

  // pointB
  opengl_->glEnableVertexAttribArray(2);
  opengl_->glBindBuffer(GL_ARRAY_BUFFER, m_pointb_buffer);
  opengl_->glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
  opengl_->glVertexAttribDivisor(2, 4);

  // width
  opengl_->glEnableVertexAttribArray(3);
  opengl_->glBindBuffer(GL_ARRAY_BUFFER, m_width_buffer);
  opengl_->glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 0, nullptr);
  opengl_->glVertexAttribDivisor(3, 4);

  // Color
  opengl_->glEnableVertexAttribArray(4);
  opengl_->glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer);
  opengl_->glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
  opengl_->glVertexAttribDivisor(4, 4);

  opengl_->glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
  opengl_->glDisableVertexAttribArray(0);
  opengl_->glDisableVertexAttribArray(1);
  opengl_->glDisableVertexAttribArray(2);
  opengl_->glDisableVertexAttribArray(3);
  opengl_->glDisableVertexAttribArray(4);
}
