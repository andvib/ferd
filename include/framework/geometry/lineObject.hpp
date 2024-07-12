#ifndef INCLUDE_FRAMEWORK_GEOMETRY_LINEOBJECT_HPP_
#define INCLUDE_FRAMEWORK_GEOMETRY_LINEOBJECT_HPP_

#include <GL/glew.h>

#include <memory>

#include "framework/OpenGLWrapper.hpp"
#include "framework/ferd_color.hpp"
#include "glm/gtc/matrix_transform.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/transform.hpp"

struct line {
  GLfloat x0;
  GLfloat y0;
  GLfloat x1;
  GLfloat y1;
  GLfloat width;
};

class LineObject {
 public:
  explicit LineObject(std::shared_ptr<OpenGLWrapper> opengl);
  LineObject(struct line points, struct ferd_color color,
             std::shared_ptr<OpenGLWrapper> opengl);
  ~LineObject() = default;

  /**
   * @brief Render a line object
   */
  void Render(void) const;

 private:
  struct line m_points;
  struct ferd_color m_color;
  GLuint m_vertexArrayID;
  GLuint m_vertexBuffer;
  GLfloat *m_vertex_buffer_data;
  GLuint m_colorBuffer;
  GLuint m_elementBuffer;
  GLuint m_pointa_buffer;
  GLuint m_pointb_buffer;
  GLuint m_width_buffer;
  std::shared_ptr<OpenGLWrapper> opengl_;
};

#endif /* INCLUDE_FRAMEWORK_GEOMETRY_LINEOBJECT_HPP_ */
