#include "game/world.hpp"

#include <spdlog/spdlog.h>

#include <chrono>
#include <vector>

void World::AddLine(const Line *line) {
  // Add LineObjects
  std::vector<std::shared_ptr<LineObject>> line_objects =
      line->GetLineObjects();
  v_LineObjects.insert(v_LineObjects.end(), line_objects.begin(),
                       line_objects.end());

  // Add waypoints
  std::vector<Waypoint *> line_waypoints = line->GetWaypoints();
  for (auto waypoint : line_waypoints) {
    if (auto *stationPtr = dynamic_cast<Station *>(waypoint)) {
      v_Stations.push_back(stationPtr);
    }
  }
}

void World::Update(clock_t delta_time_ms) const {
  for (auto trainPtr : v_Trains) {
    trainPtr->Update(delta_time_ms);
  }
}

void World::RenderRectangles(GLuint modelLoc) const {
  for (auto rectangle_ptr : v_Rectangles) {
    glm::mat4 model = rectangle_ptr->CalculateModelMatrix();
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model[0][0]);
    rectangle_ptr->Render();
  }
}

void World::RenderLineObjects() const {
  for (auto linePtr : v_LineObjects) {
    linePtr->Render();
  }
}

void World::RenderStations(GLuint modelLoc) const {
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  for (auto circlePtr : v_Stations) {
    glm::mat4 model = circlePtr->CalculateModelMatrix();
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model[0][0]);

    circlePtr->Render();
  }
  glDisable(GL_BLEND);
}
