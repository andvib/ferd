#ifndef GAME_PROGRAM_HPP__
#define GAME_PROGRAM_HPP__

#include <GL/glew.h>

#include "framework/gameShader.hpp"

class GraphicsProgram {

    private:
        GLuint ProgramID;

    public:
        /**
         * @brief Construct a new Graphics Program object
         */
        GraphicsProgram();

        void activate() {ProgramID = glCreateProgram();};

        /**
         * @brief Attach shaders to program
         * 
         * @details Attaches the shader IVs to the program. Shaders can be deleted after they have
         *          been attached.
         * 
         * @param vertex_shader Vertex shader object
         * @param fragment_shader Fragment shader object
         */
        void attachShaders(VertexShader vertex_shader, FragmentShader fragment_shader);

        /**
         * @brief Get the Program ID object
         * 
         * @return GLuint Program ID
         */
        GLuint getProgramID();

};

#endif // GAME_PROGRAM_HPP__
