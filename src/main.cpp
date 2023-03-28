#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "framework/graphicsFramework.hpp"
#include "framework/windowHandler.hpp"
#include "framework/gameShader.hpp"
#include "framework/graphicsProgram.hpp"
#include "gameTriangle.hpp"
#include "train/rectangle.hpp"
#include "game/camera.hpp"

#include "spdlog/spdlog.h"

int main(void)
{
    int err;

    spdlog::info("Hello World!");

    GraphicsFramework Framework;
    Framework.activate();

    const char *vertex_file_path = "C:/git/civ-andreas/src/shader/SimpleVertexShader.vertexshader";
    const char *fragment_file_path = "C:/git/civ-andreas/src/shader/SimpleFragmentShader.fragmentshader";

    Framework.addShaders(vertex_file_path, fragment_file_path);

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

    Camera GameCamera;
    GLuint MatrixID = glGetUniformLocation(Framework.Program.getProgramID(), "MVP");

    /* Loop until the user closes the window */
    while (Framework.isRunning())
    {
        /* Render here */
        glClearColor((245.0/255), (245.0/255), (220.0/255), 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(Framework.Program.getProgramID());

        glm::mat4 mvp = GameCamera.transform(glm::mat4(1.0f));
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);

        rectangle1.drawObject();
        rectangle2.drawObject();
        rectangle3.drawObject();
        rectangle4.drawObject();

        if(glfwGetKey(Framework.Window.getWindow(), GLFW_KEY_W) == GLFW_PRESS) {
            GameCamera.moveUp();
        }

        if(glfwGetKey(Framework.Window.getWindow(), GLFW_KEY_S) == GLFW_PRESS) {
            GameCamera.moveDown();
        }

        if(glfwGetKey(Framework.Window.getWindow(), GLFW_KEY_A) == GLFW_PRESS) {
            GameCamera.moveLeft();
        }

        if(glfwGetKey(Framework.Window.getWindow(), GLFW_KEY_D) == GLFW_PRESS) {
            GameCamera.moveRight();
        }

		/* Swap front and back buffers */
		err = Framework.Window.swapBuffers();
		if (err != 0) {
            spdlog::critical("Failed to swap buffers!");
			return -1;
		}
    }

    spdlog::info("Terminating");
    Framework.terminate();

    return 0;
}
