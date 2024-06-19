#ifndef INCLUDE_FRAMEWORK_OPENGLWRAPPER_HPP_
#define INCLUDE_FRAMEWORK_OPENGLWRAPPER_HPP_

#include <GL/glew.h>

class OpenGLWrapper {
 public:
  virtual ~OpenGLWrapper() = default;

  virtual void glBindBuffer(GLenum target, GLuint buffer) const {
    ::glBindBuffer(target, buffer);
  }

  virtual void glBindVertexArray(GLuint array) const {
    ::glBindVertexArray(array);
  }

  virtual void glBufferData(GLenum target, GLsizeiptr size, const void *data,
                            GLenum usage) const {
    ::glBufferData(target, size, data, usage);
  }

  virtual void glDisableVertexAttribArray(GLuint index) const {
    ::glDisableVertexAttribArray(index);
  }

  virtual void glDrawElements(GLenum mode, GLsizei count, GLenum type,
                              const void *indices) const {
    ::glDrawElements(mode, count, type, indices);
  }

  virtual void glEnableVertexAttribArray(GLuint index) const {
    ::glEnableVertexAttribArray(index);
  }

  virtual void glGenBuffers(GLsizei n, GLuint *buffers) const {
    ::glGenBuffers(n, buffers);
  }

  virtual void glGenVertexArrays(GLsizei n, GLuint *arrays) const {
    ::glGenVertexArrays(n, arrays);
  }

  virtual void glVertexAttribDivisor(GLuint index, GLuint divisor) const {
    ::glVertexAttribDivisor(index, divisor);
  }

  virtual void glVertexAttribPointer(GLuint index, GLint size, GLenum type,
                                     GLboolean normalized, GLsizei stride,
                                     const void *pointer) const {
    ::glVertexAttribPointer(index, size, type, normalized, stride, pointer);
  }
};

#endif /* INCLUDE_FRAMEWORK_OPENGLWRAPPER_HPP_   */
