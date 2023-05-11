#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "framework/graphicsFramework.hpp"
#include "game/camera.hpp"
#include "game/rectangleObject.hpp"
#include "game/train.hpp"

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

    struct rectangle_color rc1 = {0, 0.25, 0.75};
    struct rectangle_color rc2 = {0, 0.75, 1};
    struct rectangle_color rc3 = {0, 0.75, 0.5};
    struct rectangle_color rc4 = {0, 0.8, 0.75};
    struct rectangle_color rc5 = {0, 0.5, 0.9};

    Train trainObject(0, 3, 0.002, rc1);
    Framework.addRenderObject(&trainObject);

    Train trainObject2(1,2, 0.001, rc2);
    Framework.addRenderObject(&trainObject2);

    Train trainObject3(3,-2, 0.003, rc3);
    Framework.addRenderObject(&trainObject3);

    Train trainObject4(-2,2, 0.0007, rc4);
    Framework.addRenderObject(&trainObject4);

    Train trainObject5(-2,-2, 0.0015, rc5);
    Framework.addRenderObject(&trainObject5);

    Train trainObject6(-1,-2, 0.002, rc1);
    Framework.addRenderObject(&trainObject6);

    Train trainObject7(0.5,2, 0.0007, rc2);
    Framework.addRenderObject(&trainObject7);

    Train trainObject8(2.8,-2, 0.0022, rc3);
    Framework.addRenderObject(&trainObject8);

    Train trainObject9(-2,2, 0.0016, rc4);
    Framework.addRenderObject(&trainObject9);

    Train trainObject10(1.52,-2, 0.0017, rc5);
    Framework.addRenderObject(&trainObject10);

    spdlog::info("Starting render loop");

    Camera GameCamera;
    Framework.addCamera(&GameCamera);

    /* Loop until the user closes the window */
    clock_t lastFrame;
    while (Framework.isRunning())
    {
        clock_t curr_frame = clock();
        Framework.update((curr_frame - lastFrame) / (CLOCKS_PER_SEC/1000));

        Framework.render();

        /* Swap front and back buffers */
        Framework.swapBuffers();
        lastFrame = clock();

        clock_t sleep_time = 9 - (clock() - curr_frame);
        spdlog::debug("Sleeping for {} ms", sleep_time / (CLOCKS_PER_SEC/1000));
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time / (CLOCKS_PER_SEC/1000)));
    }

    spdlog::info("Terminating");
    Framework.terminate();

    return 0;
}
