#include "framework/graphicsFramework.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "spdlog/spdlog.h"

GraphicsFramework::GraphicsFramework()
{
    m_Window = new WindowHandler();
    m_Program = new GraphicsProgram();
    m_Screen = new GraphicsScreen();
}

GraphicsFramework::~GraphicsFramework()
{
    delete m_Window;
    delete m_Program;
    delete m_Screen;
}

int GraphicsFramework::activate()
{
    /* Initialize the library */
    glewExperimental = GL_TRUE;
    if( !glfwInit() ) {
        spdlog::critical("Failed to initalize GLFW");
    }
    spdlog::info("GLFW initialized");

    m_Window->activate();

    if (glewInit() != GLEW_OK) {
        spdlog::critical("Failed to initialize glew");
    }
    spdlog::info("GLEW initialized");

    m_Program->activate();

    return 0;
}

void GraphicsFramework::addShaders(const char *vertex_file_path, const char *fragment_file_path)
{
    VertexShader verShader;
    verShader.loadShader(vertex_file_path);
    verShader.compileShader();

    FragmentShader fragShader;
    fragShader.loadShader(fragment_file_path);
    fragShader.compileShader();

    m_Program->attachShaders(verShader, fragShader);

    verShader.deleteShader();
    fragShader.deleteShader();
}

bool GraphicsFramework::isRunning()
{
    return m_Window->isWindowRunning();
}

void GraphicsFramework::terminate()
{
    glfwTerminate();
}

void GraphicsFramework::update(clock_t delta_time_ms)
{
    m_Screen->Update(m_Program->getProgramID());
    m_Window->updateCamera(p_Camera);
    m_Window->update();

    for (auto objPtr : v_objects) {
        objPtr->Update(delta_time_ms);
    }
}

void GraphicsFramework::render()
{
    for (auto objPtr : v_objects) {
        glm::mat4 mvp = p_Camera->transform(objPtr->CalculateModelMatrix());
        glUniformMatrix4fv(m_Program->getMVPLoc(), 1, GL_FALSE, &mvp[0][0]);

        objPtr->Render();
    }
    m_Window->render();
}

void GraphicsFramework::swapBuffers()
{
    m_Window->swapBuffers();
}
