#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "windowHandler.hpp"
#include "gameShader.hpp"
#include "gameProgram.hpp"

int main(void)
{
    int err;

    /* Initialize the library */
    glewExperimental = GL_TRUE;
    if( !glfwInit() ) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    WindowHandler window;
    err = window.activate();
    if (err != 0) {
        std::cout << "Failed to open window!\n";
        return -1;
    }

    if (glewInit() != GLEW_OK) {
        std::cout << "Failed to initialize glew\n";
        return -1;
    }

    const char *vertex_file_path = "C:/git/civ-andreas/src/shader/SimpleVertexShader.vertexshader";
    const char *fragment_file_path = "C:/git/civ-andreas/src/shader/SimpleFragmentShader.fragmentshader";

    VertexShader verShader;
	verShader.loadShader(vertex_file_path);
	verShader.compileShader();

	FragmentShader fragShader;
	fragShader.loadShader(fragment_file_path);
	fragShader.compileShader();

	GameProgram program;
	program.attachShaders(verShader, fragShader);

	verShader.deleteShader();
	fragShader.deleteShader();

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
