#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "framework/windowHandler.hpp"
#include "framework/gameShader.hpp"
#include "framework/gameProgram.hpp"
#include "gameTriangle.hpp"
#include "train/rectangle.hpp"

#include "spdlog/spdlog.h"

int main(void)
{
    int err;

    spdlog::info("Hello World!");

    /* Initialize the library */
    glewExperimental = GL_TRUE;
    if( !glfwInit() ) {
        spdlog::critical("Failed to initalize GLFW");
        return -1;
    }

    WindowHandler window;
    err = window.activate();
    if (err != 0) {
        spdlog::critical("Failed to open window!");
        return -1;
    }

    if (glewInit() != GLEW_OK) {
        spdlog::critical("Failed to initialize glew");
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

    struct triangle_points t1 = {0, 0, 0, -1, -1, 0};
    struct triangle_color c1 = {1, 0, 0};
    GameTriangle triangle1(t1, c1);

    struct triangle_points t2 = {0, 0, 0, 1, 1, 0};
    struct triangle_color c2 = {0, 0, 1};
    GameTriangle triangle2(t2, c2);

    struct rectangle_points r1 = {-0.75, -0.75, -0.75, 0, 0, 0, 0, -0.75};
    struct rectangle_color rc1 = {0, 0.25, 1};
    Rectangle rectangle1(r1, rc1);

    struct rectangle_points r2 = {0.75, 0.75, 0.75, 0, 0, 0, 0, 0.75};
    struct rectangle_color rc2 = {0, 0.75, 1};
    Rectangle rectangle2(r2, rc2);

    struct rectangle_points r3 = {0, 0, 0, 0.75, -0.75, 0.75, -0.75, 0};
    struct rectangle_color rc3 = {0, 0.75, 0.5};
    Rectangle rectangle3(r3, rc3);

    struct rectangle_points r4 = {0, 0, 0, -0.75, 0.75, -0.75, 0.75, 0};
    struct rectangle_color rc4 = {0, 0.8, 0.75};
    Rectangle rectangle4(r4, rc4);

    spdlog::info("Starting render loop");

    /* Loop until the user closes the window */
    while (window.isWindowRunning())
    {
        /* Render here */
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(program.getProgramID());

        //triangle1.drawObject();
        //triangle2.drawObject();
        rectangle1.drawObject();
        rectangle2.drawObject();
        rectangle3.drawObject();
        rectangle4.drawObject();

		/* Swap front and back buffers */
		err = window.swapBuffers();
		if (err != 0) {
            spdlog::critical("Failed to swap buffers!");
			return -1;
		}
    }

    spdlog::info("Terminating");
    glfwTerminate();

    return 0;
}
