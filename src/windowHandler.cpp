#include <iostream>

#include "windowHandler.hpp"

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
        std::cout << "Failed to open GLFW window\n";
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
        std::cout << "Window hasn't been activated\n";
        return -1;
    }

    glfwSwapBuffers(window);
    glfwPollEvents();

    return 0;
}

bool WindowHandler::isWindowRunning()
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        std::cout << "Escape was pressed\n";
        return false;
    }

    if(glfwWindowShouldClose(window) != 0) {
        std::cout << "User has closed window\n";
        return false;
    }

    return true;
}
