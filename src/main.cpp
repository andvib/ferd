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

#include "game/train_util.hpp"

int main(void)
{
    int err;

    spdlog::info("Ferd.");

    GraphicsFramework Framework;
    Framework.activate();

    const char *vertex_file_path = "C:/git/ferd/src/shader/SimpleVertexShader.vertexshader";
    const char *fragment_file_path = "C:/git/ferd/src/shader/SimpleFragmentShader.fragmentshader";

    Framework.addShaders(vertex_file_path, fragment_file_path);

    struct rectangle_color rc1 = {0, 0.25, 0.75};
    struct rectangle_color rc2 = {0, 0.75, 1};
    struct rectangle_color rc3 = {0, 0.75, 0.5};
    struct rectangle_color rc4 = {0, 0.8, 0.75};
    struct rectangle_color rc5 = {0, 0.5, 0.9};

    Train trainObject(4, 0, 0.000001, rc1);
    Framework.addRenderObject(&trainObject);

    Train trainObject2(4, 1, 0.0000008, rc2);
    Framework.addRenderObject(&trainObject2);

    Train trainObject3(4, 2, 0.0000005, rc3);
    Framework.addRenderObject(&trainObject3);

    Train trainObject4(4, 3, 0.0000003, rc4);
    Framework.addRenderObject(&trainObject4);

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

        clock_t sleep_time = 20 - (clock() - curr_frame);
        spdlog::debug("Sleeping for {} ms", sleep_time / (CLOCKS_PER_SEC/1000));
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time / (CLOCKS_PER_SEC/1000)));
    }

    spdlog::info("Terminating");
    Framework.terminate();

    return 0;
}
