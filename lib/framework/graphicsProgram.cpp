#include <vector>

#include "framework/graphicsProgram.hpp"
#include "spdlog/spdlog.h"

void GraphicsProgram::attachShaders(VertexShader vertex_shader, FragmentShader fragment_shader)
{
    glAttachShader(m_ProgramID, vertex_shader.getShaderID());
    glAttachShader(m_ProgramID, fragment_shader.getShaderID());
    glLinkProgram(m_ProgramID);

    GLint Result = GL_FALSE;
    int InfoLogLength;
    glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> ProgramErrorMessage(InfoLogLength+1);
        glGetProgramInfoLog(m_ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        spdlog::critical("%s", &ProgramErrorMessage[0]);
	}

    glDetachShader(m_ProgramID, vertex_shader.getShaderID());
    glDetachShader(m_ProgramID, fragment_shader.getShaderID());
}
