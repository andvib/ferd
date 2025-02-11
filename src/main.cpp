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
#include "game/physics/kinematics.hpp"
#include "game/train.hpp"
#include "game/waypoint/station.hpp"
#include "game/waypoint/waypoint.hpp"
#include "game/world.hpp"

#include "game/rail/railPiece.hpp"
#include "game/rail/straightRailPiece.hpp"
#include "game/rail/straightRailStation.hpp"

#define CLOCKS_PER_MSEC (CLOCKS_PER_SEC / 1000)

#define WAYPOINT_X(wp) {(wp.PositionCoordinates()).x}
#define WAYPOINT_Y(wp) {(wp.PositionCoordinates()).y}

void create_line_object(World *world, Waypoint wp1, Waypoint wp2){
  struct line line = {WAYPOINT_X(wp1),
                      WAYPOINT_Y(wp1),
                      WAYPOINT_X(wp2),
                      WAYPOINT_Y(wp2),
                      0.7f};
  std::shared_ptr<LineObject> object = std::make_shared<LineObject>(line, FERD_COLOR_1,
                                                                    std::make_shared<OpenGLWrapper>());
  world->AddLineObject(object);
}


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
  Framework.AddStationShader(circle_vertex_shader_file_path,
                             circle_fragment_file_path);

  World GameWorld;
  Framework.AddWorld(&GameWorld);

  Waypoint wp1({0, 0});
  Waypoint wp2({50, -30});
  Waypoint wp3({100, -40});
  Waypoint wp4({120, -10});

  std::shared_ptr<StraightRailPiece> piece1 = std::make_shared<StraightRailPiece>();
  piece1->name = "piece1";
  piece1->waypointsSet(&wp1, &wp2);
  create_line_object(&GameWorld, wp1, wp2);

  std::shared_ptr<StraightRailStation> piece2 = std::make_shared<StraightRailStation>();
  piece2->name = "piece2";
  piece2->waypointsSet(&wp2, &wp3);
  create_line_object(&GameWorld, wp2, wp3);

  piece2->stopPointCalculate();
  Vector2D stop_point = piece2->stopPointGet();

  spdlog::info("Stop point at {}, {}", stop_point(0), stop_point(1));

  std::shared_ptr<CircleObject> circle1 = std::make_shared<CircleObject>((position_t){stop_point(0), stop_point(1)}, std::make_shared<OpenGLWrapper>());
  GameWorld.AddCircle(circle1);

  std::shared_ptr<StraightRailPiece> piece3 = std::make_shared<StraightRailPiece>();
  piece3->name = "piece3";
  piece3->waypointsSet(&wp3, &wp4);
  create_line_object(&GameWorld, wp3, wp4);

  std::shared_ptr<RailConnection> connection_1 = std::make_shared<RailConnection>(Vector2D({0, 0}));
  std::shared_ptr<RailConnection> connection_2 = std::make_shared<RailConnection>(Vector2D({50, -30}));
  std::shared_ptr<RailConnection> connection_3 = std::make_shared<RailConnection>(Vector2D({100, -40}));
  std::shared_ptr<RailConnection> connection_4 = std::make_shared<RailConnection>(Vector2D({120, -10}));

  connection_1->AddConnectionA(nullptr, nullptr);
  connection_1->AddConnectionB(piece1, connection_2);

  connection_2->AddConnectionA(piece1, connection_1);
  connection_2->AddConnectionB(piece2, connection_3);

  connection_3->AddConnectionA(piece2, connection_2);
  connection_3->AddConnectionB(piece3, connection_4);

  connection_4->AddConnectionA(piece3, connection_3);
  connection_4->AddConnectionB(nullptr, nullptr);

  Train train({0,0}, FERD_COLOR_2, piece1, connection_1);
  GameWorld.AddTrain(&train);
  GameWorld.AddRectangle(train.trainObjectGet());
  GameWorld.AddRectangle(train.trainSeekerGet());

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
