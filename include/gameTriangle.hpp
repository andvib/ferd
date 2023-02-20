#ifndef GAME_TRIANGLE_HPP__
#define GAME_TRIANGLE_HPP__

#include <GL/glew.h>

struct triangle_points {
    GLfloat x0, y0;
    GLfloat x1, y1;
    GLfloat x2, y2;
};

class GameTriangle {

    private:
        struct triangle_points points;
        GLuint VertexArrayID;
        GLuint vertexbuffer;
        GLfloat *vertex_buffer_data;

    public:
        /**
         * @brief Construct a new Game Triangle object
         *
         * @details Generates vertex array ID
         */
        GameTriangle();

        /**
         * @brief Construct a new Game Triangle object
         *
         * @details Generates a vertex array ID for the object, and assigns the three vertices to
         *          the vertex array object
         *
         * @param triangle_p Triangle struct with points for each triangle vertex
         */
        GameTriangle(struct triangle_points triangle_p);

        /**
         * @brief Draws the object
         *
         * @details Draws the triangle that has been initialized. vertexbuffer and
         *          vertex_buffer_data must've beens set by the constructor before calling this
         *          function.
         */
        void drawObject();

};

#endif /* GAME_TRIANGLE_HPP__ */
