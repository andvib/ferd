#ifndef INCLUDE_GAME_WORLD_HPP_
#define INCLUDE_GAME_WORLD_HPP_

#include <GL/glew.h>

#include <vector>

#include "framework/geometry/lineObject.hpp"
#include "game/line.hpp"
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
  void AddLine(Line *line) { v_Lines.push_back(line); }

  /**
   * @brief Add a LineObject to draw in the world
   *
   * @param object LineObject object
   */
  void AddLineObject(LineObject *object) { v_line_objects.push_back(object); }

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

 private:
  std::vector<Train *> v_Trains;
  std::vector<Line *> v_Lines;
  std::vector<LineObject *> v_line_objects;
};

#endif /* INCLUDE_GAME_WORLD_HPP_ */
