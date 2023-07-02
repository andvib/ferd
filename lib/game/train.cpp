#include "game/train.hpp"
#include "game/trainPhysics.hpp"

#include <chrono>
#include <spdlog/spdlog.h>
#include <cstdlib>
#include <ctime>

#define CLOCKS_PER_MSEC (CLOCKS_PER_SEC/1000)

static const struct rectangle_points c_train_points = {-0.25, 0.185, -0.25, -0.185, 0.25, -0.185, 0.25, 0.185};
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

Train::Train(position_t start, position_t end, float acceleration, const struct rectangle_color color) : RectangleObject(c_train_points, color)
{
    p_Physics = new TrainPhysics(start, acceleration);
    p_Route = new TrainNavigator(start, end);

    p_Physics->rotateTrain(p_Route->vectorToNextStation());
    m_State = STOPPED_AT_STATION;
}

void Train::Update(clock_t delta_time_ms)
{
    switch (m_State) {
    case STOPPED_AT_STATION:

        if (m_duration_at_station == 0) {
            vector_t vector_next = p_Route->vectorToNextStation();
            spdlog::debug("Vector: {} , {}", vector_next.x, vector_next.y);
            p_Physics->rotateTrain(vector_next);

            m_duration_at_station = clock();
            m_wait_time = rand() / (RAND_MAX/3000);
        }

        if (((clock() - m_duration_at_station) / CLOCKS_PER_MSEC) > m_wait_time) {
            m_State = ENROUTE;
            p_Physics->accelerate();
            m_duration_at_station = 0;
        }
        break;

    case ENROUTE:
        p_Physics->Update(delta_time_ms);

        if (p_Route->atStation(p_Physics->getPosition())) {
            p_Physics->stop();
            m_State = STOPPED_AT_STATION;
        }
        break;
    }

}

glm::mat4 Train::CalculateModelMatrix()
{
    position_t current_position = p_Physics->getPosition();
    vector_t vector_next = p_Physics->getRotation();
    float angle = glm::atan(vector_next.y/vector_next.x);

    glm::mat4 myTranslationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(current_position.x, current_position.y, 0.0f));
    glm::mat4 myScalingMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.75f, 0.75f, 0.75f));
    glm::mat4 myRotationMatrix = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 0.0f, 1.0f));

    return myTranslationMatrix * myRotationMatrix * myScalingMatrix;
}
