#include "framework/gameShader.hpp"

#include <GL/glew.h>
#include <stdlib.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "spdlog/spdlog.h"

GameShader::GameShader() {}

GameShader::GameShader(GLuint shader_id) { shaderID = shader_id; }

int GameShader::loadShader(const char *file_path) {
  std::ifstream ShaderStream(file_path, std::ios::in);
  if (ShaderStream.is_open()) {
    std::stringstream sstr;
    sstr << ShaderStream.rdbuf();
    shaderCode = sstr.str();
    ShaderStream.close();
  } else {
    spdlog::critical("Could not open file!");
    return -1;
  }

  return 0;
}

int GameShader::compileShader() {
  char const *SourcePointer = shaderCode.c_str();
  glShaderSource(shaderID, 1, &SourcePointer, NULL);
  glCompileShader(shaderID);

  GLint Result = GL_FALSE;
  int InfoLogLength;
  glGetShaderiv(shaderID, GL_COMPILE_STATUS, &Result);
  glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
  if (InfoLogLength > 0) {
    std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
    glGetShaderInfoLog(shaderID, InfoLogLength, NULL,
                       &VertexShaderErrorMessage[0]);
    spdlog::critical("%s", &VertexShaderErrorMessage[0]);
    return -1;
  }

  return 0;
}

GLuint GameShader::get_shader_id() { return shaderID; }

void GameShader::deleteShader() { glDeleteShader(shaderID); }
