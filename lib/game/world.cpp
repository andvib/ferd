#include "game/world.hpp"

#include <chrono>

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
