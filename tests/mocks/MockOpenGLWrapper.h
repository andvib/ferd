#ifndef TESTS_MOCKS_MOCKOPENGLWRAPPER_H_
#define TESTS_MOCKS_MOCKOPENGLWRAPPER_H_

#include <gmock/gmock.h>

#include "framework/OpenGLWrapper.hpp"

class MockOpenGLWrapper : public OpenGLWrapper {
 public:
  MOCK_METHOD(void, glBindBuffer, (GLenum target, GLuint buffer),
              (const, override));

  MOCK_METHOD(void, glBindVertexArray, (GLuint array), (const, override));

  MOCK_METHOD(void, glBufferData,
              (GLenum target, GLsizeiptr size, const void *data, GLenum usage),
              (const, override));

  MOCK_METHOD(void, glDisableVertexAttribArray, (GLuint index),
              (const, override));

  MOCK_METHOD(void, glDrawElements,
              (GLenum mode, GLsizei count, GLenum type, const void *indices),
              (const, override));

  MOCK_METHOD(void, glEnableVertexAttribArray, (GLuint index),
              (const, override));

  MOCK_METHOD(void, glGenBuffers, (GLsizei n, GLuint *buffers),
              (const, override));

  MOCK_METHOD(void, glGenVertexArrays, (GLsizei n, GLuint *arrays),
              (const, override));

  MOCK_METHOD(void, glVertexAttribPointer,
              (GLuint index, GLint size, GLenum type, GLboolean normalized,
               GLsizei stride, const void *pointer),
              (const, override));
};

#endif /* TESTS_MOCKS_MOCKOPENGLWRAPPER_H_   */
