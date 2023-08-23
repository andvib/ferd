#include "framework/graphicsProgram.hpp"

#include <vector>

#include "spdlog/spdlog.h"

void GraphicsProgram::AttachShaders(VertexShader vertex_shader,
                                    FragmentShader fragment_shader) {
  glAttachShader(m_program_id, vertex_shader.get_shader_id());
  glAttachShader(m_program_id, fragment_shader.get_shader_id());
  glLinkProgram(m_program_id);

  GLint Result = GL_FALSE;
  int InfoLogLength;
  glGetProgramiv(m_program_id, GL_LINK_STATUS, &Result);
  glGetProgramiv(m_program_id, GL_INFO_LOG_LENGTH, &InfoLogLength);
  if (InfoLogLength > 0) {
    std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
    glGetProgramInfoLog(m_program_id, InfoLogLength, NULL,
                        &ProgramErrorMessage[0]);
    spdlog::critical("%s", &ProgramErrorMessage[0]);
  }

  glDetachShader(m_program_id, vertex_shader.get_shader_id());
  glDetachShader(m_program_id, fragment_shader.get_shader_id());
}
