#include <iostream>

#include "framework/windowHandler.hpp"
#include "spdlog/spdlog.h"

WindowHandler::WindowHandler()
{
    window = NULL;

    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Opengl 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

int WindowHandler::activate()
{
    window = glfwCreateWindow(1024, 768, "Hello World", NULL, NULL);
    if(window == NULL) {
        spdlog::critical("Failed to open GLFW window");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    return 0;
}

int WindowHandler::swapBuffers()
{
    if (window == NULL) {
        spdlog::critical("Window hasn't been activated");
        return -1;
    }

    glfwSwapBuffers(window);
    glfwPollEvents();

    return 0;
}

bool WindowHandler::isWindowRunning()
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        spdlog::debug("Escape was pressed");
        return false;
    }

    if(glfwWindowShouldClose(window) != 0) {
        spdlog::debug("User has closed window");
        return false;
    }

    return true;
}
