#include "game/train.hpp"
#include <spdlog/spdlog.h>

static const struct rectangle_points c_train_points = {-0.25, 0.25, -0.25, -0.25, 0.25, -0.25, 0.25, 0.25};
static const struct rectangle_color c_default_color = {0, 0.25, 1};

Train::Train() : RectangleObject(c_train_points, c_default_color)
{
}

Train::Train(float x, float y, const struct rectangle_color color) : RectangleObject(c_train_points, color)
{
    m_move_x = x;
    m_move_y = y;
}

Train::Train(float x, float y, float speed, const struct rectangle_color color) : RectangleObject(c_train_points, color)
{
    m_move_x = x;
    m_move_y = y;
    m_speed = speed;
}

void Train::Update(clock_t delta_time_ms)
{
    float distanceTravelled = m_speed * delta_time_ms;

    if (m_move_x >= 3.0f) {
        m_dir_x = 1;
    }
    if (m_move_x <= -3.0f) {
        m_dir_x = 0;
    }
    if (m_dir_x == 1) {
        m_move_x -= distanceTravelled;
    } else {
        m_move_x += distanceTravelled;
    }

    if (m_move_y >= 3.5f) {
        m_dir_y = 1;
    }
    if (m_move_y <= -3.5f) {
        m_dir_y = 0;
    }
    if (m_dir_y == 1) {
        m_move_y -= distanceTravelled;
    } else {
        m_move_y += distanceTravelled;
    }
}

glm::mat4 Train::CalculateModelMatrix()
{
    glm::mat4 myTranslationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(m_move_x, m_move_y, 0.0f));
    glm::mat4 myScalingMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.75f, 0.75f, 0.75f));
    glm::mat4 myRotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));

    return myTranslationMatrix * myRotationMatrix * myScalingMatrix;
}
