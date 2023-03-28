#include "framework/graphicsFramework.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "spdlog/spdlog.h"


int GraphicsFramework::activate()
{
    /* Initialize the library */
    glewExperimental = GL_TRUE;
    if( !glfwInit() ) {
        spdlog::critical("Failed to initalize GLFW");
    }
    spdlog::info("GLFW initialized");

    Window.activate();

    if (glewInit() != GLEW_OK) {
        spdlog::critical("Failed to initialize glew");
    }
    spdlog::info("GLEW initialized");

    Program.activate();
    
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

    Program.attachShaders(verShader, fragShader);

    verShader.deleteShader();
    fragShader.deleteShader();
}

bool GraphicsFramework::isRunning()
{
    return Window.isWindowRunning();
}

void GraphicsFramework::terminate()
{
    glfwTerminate();
}
