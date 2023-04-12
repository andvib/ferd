#ifndef RECTANGLE_OBJECT_HPP__
#define RECTANGLE_OBJECT_HPP__

#include <GL/glew.h>

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"

struct rectangle_points {
    GLfloat x0, y0;
    GLfloat x1, y1;
    GLfloat x2, y2;
    GLfloat x3, y3;
};

struct rectangle_color {
    GLfloat red, green, blue;
};

class RectangleObject
{

    public:
        RectangleObject();
        RectangleObject(struct rectangle_points rectangle_p, struct rectangle_color color);

        /**
         * @brief Update attributes of the rectangle object
         *
         * @details Updates the position and calculates the model matrix
         */
        void Update(void);

        /**
         * @brief Render the rectangle object
         */
        void Render(void);

        /**
         * @brief Get the Model Matrix object
         * 
         * @return glm::mat4 
         */
        glm::mat4 GetModelMatrix() { return m_ModelMatrix; };

    private:
        struct rectangle_points m_points;
        struct rectangle_color m_color;
        GLuint m_vertexArrayID;
        GLuint m_vertexBuffer;
        GLfloat *m_vertex_buffer_data;
        GLuint m_colorBuffer;
        GLuint m_elementBuffer;
        float m_move_x = 0;
        float m_move_y = 0;
        int m_dir_x = 0;
        int m_dir_y = 0;
        glm::mat4 m_ModelMatrix;
};

#endif /* RECTANGLE_OBJECT_HPP__ */
