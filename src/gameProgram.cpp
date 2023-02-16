#include <vector>
#include "gameProgram.hpp"

GameProgram::GameProgram()
{
    ProgramID = glCreateProgram();
}

void GameProgram::attachShaders(VertexShader vertex_shader, FragmentShader fragment_shader)
{
    glAttachShader(ProgramID, vertex_shader.getShaderID());
    glAttachShader(ProgramID, fragment_shader.getShaderID());
    glLinkProgram(ProgramID);

    GLint Result = GL_FALSE;
    int InfoLogLength;
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

    glDetachShader(ProgramID, vertex_shader.getShaderID());
	glDetachShader(ProgramID, fragment_shader.getShaderID());
}

GLuint GameProgram::getProgramID()
{
    return ProgramID;
}
