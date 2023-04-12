#include "game/rectangleObject.hpp"
#include <spdlog/spdlog.h>

RectangleObject::RectangleObject()
{
    glGenVertexArrays(1, &m_vertexArrayID);
}

RectangleObject::RectangleObject(struct rectangle_points rectangle_p, struct rectangle_color color)
{
    glGenVertexArrays(1, &m_vertexArrayID);
    glBindVertexArray(m_vertexArrayID);

    m_points = rectangle_p;

    GLfloat m_VertexBufferData[] {
        m_points.x0, m_points.y0, 0.0f,
        m_points.x1, m_points.y1, 0.0f,
        m_points.x2, m_points.y2, 0.0f,
        m_points.x3, m_points.y3, 0.0f
    };

    glGenBuffers(1, &m_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_VertexBufferData), m_VertexBufferData, GL_STATIC_DRAW);

    GLuint indices[] {
        0, 1, 3,
        2, 3, 1
    };

    glGenBuffers(1, &m_elementBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    GLfloat color_buffer_data[] {
        color.red, color.green, color.blue,
        color.red, color.green, color.blue,
        color.red, color.green, color.blue,
        color.red, color.green, color.blue
    };

    glGenBuffers(1, &m_colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data, GL_STATIC_DRAW);
}

void RectangleObject::Update()
{
    glm::mat4 myTranslationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(m_move_x, m_move_y, 0.0f));
    glm::mat4 myScalingMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.75f, 0.75f, 0.75f));
    glm::mat4 myRotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));

    m_ModelMatrix = myTranslationMatrix * myRotationMatrix * myScalingMatrix;

    if (m_move_x >= 3.0f) {
        m_dir_x = 1;
    }
    if (m_move_x <= -3.0f) {
        m_dir_x = 0;
    }
    if (m_dir_x == 1) {
        m_move_x -= 0.07;
    } else {
        m_move_x += 0.07;
    }

    if (m_move_y >= 3.0f) {
        m_dir_y = 1;
    }
    if (m_move_y <= -3.0f) {
        m_dir_y = 0;
    }
    if (m_dir_y == 1) {
        m_move_y -= 0.065;
    } else {
        m_move_y += 0.065;
    }
}

void RectangleObject::Render(void)
{
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        0,
        (void*)0
    );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBuffer);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer);
    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        0,
        (void*)0
    );

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}
