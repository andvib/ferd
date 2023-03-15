#include "gameTriangle.hpp"
#include <cstdio>

GameTriangle::GameTriangle()
{
    glGenVertexArrays(1, &VertexArrayID);
}

GameTriangle::GameTriangle(struct triangle_points triangle_p, struct triangle_color color)
{
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    points = triangle_p;

    printf("(%f, %f), (%f, %f), (%f, %f)\n",
            points.x0, points.y0,
            points.x1, points.y1,
            points.x2, points.y2);

    GLfloat vertex_buffer_data[] {
        points.x0, points.y0, 0.0f,
        points.x1, points.y1, 0.0f,
        points.x2, points.y2, 0.0f
    };

    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &vertexbuffer);
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);

    GLfloat color_buffer_data[] {
        color.r, color.g, color.b,
        color.r, color.g, color.b,
        color.r, color.g, color.b
    };

    printf("colors: (%f, %f, %f)\n", color_buffer_data[0], color_buffer_data[1], color_buffer_data[2]);

    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data, GL_STATIC_DRAW);
}

void GameTriangle::drawObject()
{
    // 1st attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
        0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        0,
        (void*)0
    );

    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}