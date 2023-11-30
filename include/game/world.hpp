#ifndef INCLUDE_GAME_WORLD_HPP_
#define INCLUDE_GAME_WORLD_HPP_

#include <GL/glew.h>

#include <vector>

#include "framework/geometry/circleObject.hpp"
#include "framework/geometry/lineObject.hpp"
#include "game/line.hpp"
#include "game/lineWaypoint.hpp"
#include "game/train.hpp"

class World {
 public:
  World() {}
  ~World() {}

  /**
   * @brief Update world objects
   *
   * @param delta_time_ms
   */
  void Update(clock_t delta_time_ms);

  /**
   * @brief Add a train to the world
   *
   * @param train Train object to be added
   */
  void AddTrain(Train *train) { v_Trains.push_back(train); }

  /**
   * @brief Add a train line to the world
   *
   * @param line Line object to be added
   */
  void AddLine(const Line *line);

  /**
   * @brief Add a LineObject to draw in the world
   *
   * @param object LineObject object
   */
  void AddLineObject(LineObject *object) { v_line_objects.push_back(object); }

  void AddLineObjectVector(std::vector<LineObject *> lines) {
    v_line_objects.insert(v_line_objects.end(), lines.begin(), lines.end());
  }

  /**
   * @brief Add LineWaypoint to draw in the world
   *
   * @param wp Waypoint to draw
   */
  void AddLineWaypoint(LineWaypoint *wp) { v_line_waypoints.push_back(wp); }

  /**
   * @brief Render the trains in the world
   *
   * @param modelLoc Location of the model uniform in the program
   */
  void RenderTrains(GLuint modelLoc);

  /**
   * @brief Render the line objects in the world
   */
  void RenderLineObjects();

  /**
   * @brief Render line waypoints (circles) in the world
   *
   * @param modelLoc Location of the model uniform in the program
   */
  void RenderLineWaypoints(GLuint modelLoc) const;

 private:
  std::vector<Train *> v_Trains;
  std::vector<Line *> v_Lines;
  std::vector<LineObject *> v_line_objects;
  std::vector<LineWaypoint *> v_line_waypoints;
};

#endif /* INCLUDE_GAME_WORLD_HPP_ */
