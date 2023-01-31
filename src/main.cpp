#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "windowHandler.hpp"


int main(void)
{
    int err;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    WindowHandler window;
    err = window.activate();
    if (err != 0) {
        std::cout << "Failed to open window!\n";
        return -1;
    }

    /* Loop until the user closes the window */
    while (window.isWindowRunning())
    {
        /* Render here */
        glClearColor(1.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        err = window.swapBuffers();
        if (err != 0) {
            std::cout << "Failed to swap buffers!\n";
            return -1;
        }
    }

    glfwTerminate();

    return 0;
}