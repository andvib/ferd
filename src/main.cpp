#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "framework/graphicsFramework.hpp"
#include "game/camera.hpp"
#include "game/rectangleObject.hpp"

#include <chrono>
#include <ctime>
#include <iostream>
#include <spdlog/spdlog.h>
#include <thread>

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
    RectangleObject rectangle1(r1, rc1);

    struct rectangle_points r2 = {0.75, 0.75, 0.75, 0, 0, 0, 0, 0.75};
    struct rectangle_color rc2 = {0, 0.75, 1};
    RectangleObject rectangle2(r2, rc2);

    struct rectangle_points r3 = {0, 0, 0, 0.75, -0.75, 0.75, -0.75, 0};
    struct rectangle_color rc3 = {0, 0.75, 0.5};
    RectangleObject rectangle3(r3, rc3);

    struct rectangle_points r4 = {0, 0, 0, -0.75, 0.75, -0.75, 0.75, 0};
    struct rectangle_color rc4 = {0, 0.8, 0.75};
    RectangleObject rectangle4(r4, rc4);

    Framework.addRenderObject(&rectangle1);
    Framework.addRenderObject(&rectangle2);
    Framework.addRenderObject(&rectangle3);
    Framework.addRenderObject(&rectangle4);

    spdlog::info("Starting render loop");

    Camera GameCamera;
    Framework.addCamera(&GameCamera);

    /* Loop until the user closes the window */
    while (Framework.isRunning())
    {
        clock_t curr_frame = clock();
        Framework.update();

        Framework.render();

        /* Swap front and back buffers */
        Framework.swapBuffers();

        clock_t sleep_time = 16 - (clock() - curr_frame);
        spdlog::debug("Sleeping for {} ms", sleep_time / (CLOCKS_PER_SEC/1000));
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time / (CLOCKS_PER_SEC/1000)));
    }

    spdlog::info("Terminating");
    Framework.terminate();

    return 0;
}
