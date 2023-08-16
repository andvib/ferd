#ifndef INCLUDE_GAME_WORLD_HPP_
#define INCLUDE_GAME_WORLD_HPP_

#include <GL/glew.h>

#include <vector>

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

  void RenderTrains(GLuint modelLoc);

  void RenderLines(GLuint modelLoc);

 private:
  std::vector<Train *> v_Trains;
  std::vector<Line *> v_Lines;
};

#endif /* INCLUDE_GAME_WORLD_HPP_ */
