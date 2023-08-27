#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

#include "framework/graphicsFramework.hpp"
#include "game/camera.hpp"
#include "game/line.hpp"
#include "game/train.hpp"
#include "game/train_util.hpp"
#include "game/world.hpp"

#define CLOCKS_PER_MSEC (CLOCKS_PER_SEC / 1000)

int main(void) {
  int err;

  spdlog::info("Ferd.");

  GraphicsFramework Framework;
  Framework.Activate();

  const char *vertex_file_path =
      "C:/git/ferd/src/shader/SimpleVertexShader.vertexshader";
  const char *fragment_file_path =
      "C:/git/ferd/src/shader/SimpleFragmentShader.fragmentshader";

  Framework.AddTrainShader(vertex_file_path, fragment_file_path);

  World GameWorld;
  Framework.AddWorld(&GameWorld);

  struct rectangle_color rc1 = {0, 0.25, 0.75};
  struct rectangle_color rc2 = {0, 0.75, 1};
  struct rectangle_color rc3 = {0, 0.75, 0.5};
  struct rectangle_color rc4 = {0, 0.8, 0.75};
  struct rectangle_color rc5 = {0, 0.5, 0.9};

  LineWaypoint wp1({4, 0}, true);
  LineWaypoint wp2({2, -3}, true);
  LineWaypoint wp3({-2, -4}, true);
  LineWaypoint wp4({-4, 0}, true);

  Line line1({std::vector<LineWaypoint *>{&wp1, &wp2, &wp3, &wp4}});

  Train trainObject(&line1, {4, 0}, 0.0000005, rc1);
  GameWorld.AddTrain(&trainObject);

  Train trainObject2(&line1, {4, 0}, 0.0000005, rc1);
  GameWorld.AddTrain(&trainObject2);

  LineWaypoint wp2_0({-4, -4}, true);
  LineWaypoint wp2_1({-1, -3}, true);
  LineWaypoint wp2_2({-1, 0}, true);
  LineWaypoint wp2_3({0, 2}, true);
  LineWaypoint wp2_4({3, 4}, true);

  Line line2{
      std::vector<LineWaypoint *>{&wp2_0, &wp2_1, &wp2_2, &wp2_3, &wp2_4}};

  Train trainObject3(&line2, {-4, -4}, 0.0000005, rc2);
  GameWorld.AddTrain(&trainObject3);

  Train trainObject4(&line2, {-4, -4}, 0.0000005, rc2);
  GameWorld.AddTrain(&trainObject4);

  LineWaypoint wp3_0({4, 0}, true);
  LineWaypoint wp3_1({1, 0}, true);
  LineWaypoint wp3_2({-1, 2}, true);
  LineWaypoint wp3_3({-3, 4}, true);

  Line line3{std::vector<LineWaypoint *>{&wp3_0, &wp3_1, &wp3_2, &wp3_3}};

  Train trainObject5(&line3, {4, 0}, 0.0000005, rc3);
  GameWorld.AddTrain(&trainObject5);

  Train trainObject6(&line3, {-4, 0}, 0.0000005, rc3);
  GameWorld.AddTrain(&trainObject6);

  spdlog::info("Starting render loop");

  Camera GameCamera;
  Framework.addCamera(&GameCamera);

  /* Loop until the user closes the window */
  clock_t lastFrame = clock();
  while (Framework.isRunning()) {
    clock_t curr_frame = clock();
    float delta_time_ms = (curr_frame - lastFrame) / CLOCKS_PER_MSEC;
    Framework.Update(delta_time_ms);
    spdlog::debug("Time since last frame: {0} ms ({1:.2f} FPS)", delta_time_ms,
                  (1 / delta_time_ms) * 1000);
    Framework.Render();

    /* Swap front and back buffers */
    Framework.swapBuffers();
    lastFrame = curr_frame;
  }

  spdlog::info("Terminating");
  Framework.terminate();

  return 0;
}
