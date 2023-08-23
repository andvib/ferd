#ifndef INCLUDE_FRAMEWORK_GRAPHICSPROGRAM_HPP_
#define INCLUDE_FRAMEWORK_GRAPHICSPROGRAM_HPP_

#include <GL/glew.h>

#include "framework/gameShader.hpp"

class GraphicsProgram {
 public:
  /**
   * @brief Construct a new Graphics Program object
   */
  GraphicsProgram() {}

  /**
   * @brief Activate an OpenGL program
   */
  void Create() { m_program_id = glCreateProgram(); }

  /**
   * @brief Enable the program as the current context
   */
  void EnableProgram() { glUseProgram(m_program_id); }

  /**
   * @brief Attach shaders to program
   *
   * @details Attaches the shader IVs to the program. Shaders can be deleted
   * after they have been attached.
   *
   * @param vertex_shader Vertex shader object
   * @param fragment_shader Fragment shader object
   */
  void AttachShaders(VertexShader vertex_shader,
                     FragmentShader fragment_shader);

  /**
   * @brief Get the Program ID object
   *
   * @return GLuint Program ID
   */
  GLuint get_program_id() { return m_program_id; }

 private:
  GLuint m_program_id;
};

#endif /* INCLUDE_FRAMEWORK_GRAPHICSPROGRAM_HPP_ */
