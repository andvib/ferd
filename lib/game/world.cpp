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
