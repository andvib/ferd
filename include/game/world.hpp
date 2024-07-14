#ifndef INCLUDE_GAME_WORLD_HPP_
#define INCLUDE_GAME_WORLD_HPP_

#include <GL/glew.h>

#include <memory>
#include <vector>

#include "framework/geometry/circleObject.hpp"
#include "framework/geometry/lineObject.hpp"
#include "game/line.hpp"
#include "game/train.hpp"
#include "game/waypoint/station.hpp"

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
  void AddLineObject(std::shared_ptr<LineObject> object) {
    v_LineObjects.push_back(object);
  }

  void AddLineObjectVector(std::vector<std::shared_ptr<LineObject>> lines) {
    v_LineObjects.insert(v_LineObjects.end(), lines.begin(), lines.end());
  }

  /**
   * @brief Add Station to be drawn in the world
   *
   * @param station Station to draw
   */
  void AddStation(Station *station) { v_Stations.push_back(station); }

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
   * @brief Render stations in the world
   *
   * @param modelLoc Location of the model uniform in the program
   */
  void RenderStations(GLuint modelLoc) const;

 private:
  std::vector<Train *> v_Trains;
  std::vector<Line *> v_Lines;
  std::vector<std::shared_ptr<LineObject>> v_LineObjects;
  std::vector<Station *> v_Stations;
};

#endif /* INCLUDE_GAME_WORLD_HPP_ */
