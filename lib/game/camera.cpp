#include "game/camera.hpp"
#include "spdlog/spdlog.h"

Camera::Camera()
{
    Position = {0,0};
    Dimensions = {-5.0f, 5.0f, -5.0f, 5.0f};
    Speed = 0.1;
}

glm::mat4 Camera::transform(glm::mat4 model_matrix)
{
    glm::mat4 View = glm::lookAt(
        glm::vec3(Position.x, Position.y, 5), // Position of camera
        glm::vec3(Position.x, Position.y, 0), // Point camera looks at
        glm::vec3(0,1,0)  // Up vector
    );

    glm::mat4 Projection = glm::ortho(Dimensions.left, Dimensions.right,
                                      Dimensions.bottom, Dimensions.top,
                                      0.0f, 100.0f);

    return Projection * View * model_matrix;
}
