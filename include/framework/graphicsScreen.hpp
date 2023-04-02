#ifndef GRAPHICS_SCREEN_HPP__
#define GRAPHICS_SCREEN_HPP__

#include <GL/glew.h>

class GraphicsScreen {

    public:
        GraphicsScreen() {};

        /**
         * @brief Update the screen for a new buffer
         *
         * @details Sets the GL clear attributes and selects the GL program
         * 
         * @param ProgramID ID of the GL program to be used
         */
        void Update(GLuint ProgramID);
};

#endif /* GRAPHICS_SCREEN_HPP__ */
