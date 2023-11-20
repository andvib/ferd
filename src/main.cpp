#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

#include "framework/ferd_color.hpp"
#include "framework/geometry/lineObject.hpp"
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
  const char *line_vertex_shader_file_path =
      "C:/git/ferd/src/shader/LineVertexShader.vertexshader";
  const char *circle_vertex_shader_file_path =
      "C:/git/ferd/src/shader/CircleVertexShader.vertexshader";
  const char *circle_fragment_file_path =
      "C:/git/ferd/src/shader/CircleFragmentShader.fragmentshader";

  Framework.AddTrainShader(vertex_file_path, fragment_file_path);
  Framework.AddLineShader(line_vertex_shader_file_path, fragment_file_path);
  Framework.AddWaypointShader(circle_vertex_shader_file_path,
                              circle_fragment_file_path);

  World GameWorld;
  Framework.AddWorld(&GameWorld);

  LineWaypoint wp1({0, 0}, FERD_COLOR_1);
  LineWaypoint wp2({50, -30}, FERD_COLOR_1);
  LineWaypoint wp3({100, -40}, FERD_COLOR_1);
  LineWaypoint wp4({120, -10}, FERD_COLOR_1);

  GameWorld.AddLineWaypoint(&wp1);
  GameWorld.AddLineWaypoint(&wp2);
  GameWorld.AddLineWaypoint(&wp3);
  GameWorld.AddLineWaypoint(&wp4);

  Line line1(std::vector<LineWaypoint *>{&wp1, &wp2, &wp3, &wp4}, FERD_COLOR_1);
  GameWorld.AddLineObjectVector(line1.GetLineObjects());

  Train trainObject(&line1, {0, 0}, 2, FERD_COLOR_1);
  GameWorld.AddTrain(&trainObject);

  Train trainObject2(&line1, {0, 0}, 3, FERD_COLOR_1);
  GameWorld.AddTrain(&trainObject2);

  LineWaypoint wp2_0({100, -100}, FERD_COLOR_2);
  LineWaypoint wp2_1({100, -40}, FERD_COLOR_2);
  LineWaypoint wp2_2({100, -5}, FERD_COLOR_2);
  LineWaypoint wp2_3({80, 35}, FERD_COLOR_2);
  LineWaypoint wp2_4({20, 30}, FERD_COLOR_2);
  LineWaypoint wp2_5({-30, 50}, FERD_COLOR_2);

  GameWorld.AddLineWaypoint(&wp2_0);
  GameWorld.AddLineWaypoint(&wp2_1);
  GameWorld.AddLineWaypoint(&wp2_2);
  GameWorld.AddLineWaypoint(&wp2_3);
  GameWorld.AddLineWaypoint(&wp2_4);
  GameWorld.AddLineWaypoint(&wp2_5);

  Line line2(std::vector<LineWaypoint *>{&wp2_0, &wp2_1, &wp2_2, &wp2_3, &wp2_4,
                                         &wp2_5},
             FERD_COLOR_2);
  GameWorld.AddLineObjectVector(line2.GetLineObjects());

  Train trainObject3(&line2, {100, -100}, 3, FERD_COLOR_2);
  GameWorld.AddTrain(&trainObject3);

  Train trainObject4(&line2, {100, -100}, 3, FERD_COLOR_2);
  GameWorld.AddTrain(&trainObject4);

  LineWaypoint wp3_0({80, 35}, FERD_COLOR_3);
  LineWaypoint wp3_1({50, 5}, FERD_COLOR_3);
  LineWaypoint wp3_2({50, -30}, FERD_COLOR_3);
  LineWaypoint wp3_3({-10, -45}, FERD_COLOR_3);

  GameWorld.AddLineWaypoint(&wp3_0);
  GameWorld.AddLineWaypoint(&wp3_1);
  GameWorld.AddLineWaypoint(&wp3_2);
  GameWorld.AddLineWaypoint(&wp3_3);

  Line line3(std::vector<LineWaypoint *>{&wp3_0, &wp3_1, &wp3_2, &wp3_3},
             FERD_COLOR_3);
  GameWorld.AddLineObjectVector(line3.GetLineObjects());

  Train trainObject5(&line3, {80, 35}, 3, FERD_COLOR_3);
  GameWorld.AddTrain(&trainObject5);

  Train trainObject6(&line3, {80, 35}, 3, FERD_COLOR_3);
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
