#include "framework/graphicsScreen.hpp"

void GraphicsScreen::Update(GLuint ProgramID)
{
    glClearColor((245.0/255), (245.0/255), (220.0/255), 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(ProgramID);
}
