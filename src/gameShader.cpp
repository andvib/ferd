#include <stdlib.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include <GL/glew.h>

#include "gameShader.hpp"

GameShader::GameShader()
{

}

GameShader::GameShader(GLuint shader_id)
{
    shaderID = shader_id;
}

int GameShader::loadShader(const char *file_path)
{
    std::ifstream ShaderStream(file_path, std::ios::in);
    if(ShaderStream.is_open()) {
        std::stringstream sstr;
        sstr << ShaderStream.rdbuf();
        shaderCode = sstr.str();
        ShaderStream.close();
    } else {
        std::cout << "Could not open file!\n";
        return -1;
    }

    return 0;
}

int GameShader::compileShader()
{
    char const * SourcePointer = shaderCode.c_str();
    glShaderSource(shaderID, 1, &SourcePointer, NULL);
    glCompileShader(shaderID);

    GLint Result = GL_FALSE;
    int InfoLogLength;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if(InfoLogLength > 0) {
        std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(shaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
        printf("%s\n", &VertexShaderErrorMessage[0]);
        return -1;
    }

    return 0;
}

GLuint GameShader::getShaderID()
{
    return shaderID;
}

void GameShader::deleteShader()
{
    glDeleteShader(shaderID);
}
