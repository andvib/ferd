#include "game/train.hpp"
#include "game/trainPhysics.hpp"

#include <spdlog/spdlog.h>

static const struct rectangle_points c_train_points = {-0.25, 0.25, -0.25, -0.25, 0.25, -0.25, 0.25, 0.25};
static const struct rectangle_color c_default_color = {0, 0.25, 1};

Train::Train() : RectangleObject(c_train_points, c_default_color)
{
    p_Route = new TrainNavigator();
    p_Physics = new TrainPhysics();
}

Train::~Train()
{
    delete p_Route;
    delete p_Physics;
}

Train::Train(float x, float y, float acceleration, const struct rectangle_color color) : RectangleObject(c_train_points, color)
{
    p_Physics = new TrainPhysics({x,y}, acceleration);
    p_Route = new TrainNavigator({x,y}, {-x,y});
}

void Train::Update(clock_t delta_time_ms)
{
    p_Physics->Update(delta_time_ms);

    if (p_Route->atStation(p_Physics->getPosition())) {
        spdlog::info("Train reached station");

        p_Physics->changeDirection();
        p_Physics->stop();
    }
}

glm::mat4 Train::CalculateModelMatrix()
{
    position_t current_position = p_Physics->getPosition();

    glm::mat4 myTranslationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(current_position.x, current_position.y, 0.0f));
    glm::mat4 myScalingMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.75f, 0.75f, 0.75f));
    glm::mat4 myRotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));

    return myTranslationMatrix * myRotationMatrix * myScalingMatrix;
}
