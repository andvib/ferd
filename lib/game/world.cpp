#include "game/world.hpp"

#include <chrono>

void World::AddLine(const Line *line) {
  // Add LineObjects
  std::vector<LineObject *> line_objects = line->GetLineObjects();
  v_line_objects.insert(v_line_objects.end(), line_objects.begin(),
                        line_objects.end());
  // Add waypoints
  std::vector<LineWaypoint *> line_waypoints = line->GetLineWaypoints();
  for (auto waypoint : line_waypoints) {
    if (waypoint->IsStation()) {
      v_line_waypoints.push_back(waypoint);
    }
  }
}

void World::Update(clock_t delta_time_ms) {
  for (auto trainPtr : v_Trains) {
    trainPtr->Update(delta_time_ms);
  }
}

void World::RenderTrains(GLuint modelLoc) {
  for (auto trainPtr : v_Trains) {
    glm::mat4 model = trainPtr->CalculateModelMatrix();
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model[0][0]);

    trainPtr->Render();
  }
}

void World::RenderLineObjects() {
  for (auto linePtr : v_line_objects) {
    linePtr->Render();
  }
}

void World::RenderLineWaypoints(GLuint modelLoc) const {
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  for (auto circlePtr : v_line_waypoints) {
    glm::mat4 model = circlePtr->CalculateModelMatrix();
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model[0][0]);

    circlePtr->Render();
  }
  glDisable(GL_BLEND);
}
