#ifndef INCLUDE_FRAMEWORK_GEOMETRY_LINEOBJECT_HPP_
#define INCLUDE_FRAMEWORK_GEOMETRY_LINEOBJECT_HPP_

#include <GL/glew.h>

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"

struct line {
  GLfloat x0, y0;
  GLfloat x1, y1;
  GLfloat width;
};

struct line_color {
  GLfloat red, green, blue;
};

class LineObject {
 public:
  LineObject();
  LineObject(struct line points, struct line_color color);

  /**
   * @brief Render a line object
   */
  void Render(void);

 private:
  struct line m_points;
  struct line_color m_color;
  GLuint m_vertexArrayID;
  GLuint m_vertexBuffer;
  GLfloat *m_vertex_buffer_data;
  GLuint m_colorBuffer;
  GLuint m_elementBuffer;
  GLuint m_pointa_buffer;
  GLuint m_pointb_buffer;
  GLuint m_width_buffer;
};

#endif /* INCLUDE_FRAMEWORK_GEOMETRY_LINEOBJECT_HPP_ */
