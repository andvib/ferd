#ifndef RECTANGLE_HPP__
#define RECTANGLE_HPP__

#include <GL/glew.h>

struct rectangle_points {
    GLfloat x0, y0;
    GLfloat x1, y1;
    GLfloat x2, y2;
    GLfloat x3, y3;
};

struct rectangle_color {
    GLfloat red, green, blue;
};

class Rectangle {

    private:
        struct rectangle_points points;
        struct rectangle_color color;
        GLuint VertexArrayID;
        GLuint vertexbuffer;
        GLfloat *vertex_buffer_data;
        GLuint colorbuffer;
        GLuint elementbuffer;

    public:
        /**
         * @brief Construct a new Rectangle object
         *
         * @details Generates vertex arary ID
         */
        Rectangle();

        /**
         * @brief Construct a new Rectangle object
         *
         * @details Generates a vertex array ID for the object, and generates the vertices needed
         *          to draw the rectangle
         *
         * @param rectangle_points Rectangle struct with points for each corner
         * @param color Struct holding the solid color of the rectangle
         */
        Rectangle(struct rectangle_points, struct rectangle_color color);

        /**
         * @brief Draws the object
         *
         * @details Draws the rectangle that has been initialized. Vertex, element and color buffer
         *          must have been set by the constructor before calling this function.
         */
        void drawObject();
};

#endif /* RECTANGLE_HPP__ */
