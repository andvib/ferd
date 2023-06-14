#ifndef GAME_PROGRAM_HPP__
#define GAME_PROGRAM_HPP__

#include <GL/glew.h>

#include "framework/gameShader.hpp"

class GraphicsProgram {

    private:
        GLuint m_ProgramID;

    public:
        /**
         * @brief Construct a new Graphics Program object
         */
        GraphicsProgram() {};

        /**
         * @brief Activate an OpenGL program
         */
        void activate() {m_ProgramID = glCreateProgram();};

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
        GLuint getProgramID() {return m_ProgramID;};

        /**
         * @brief Get the location of the view-projection (VP) uniform
         *
         * @return GLuint Location ID for the VP uniform
         */
        GLuint getViewProjLoc() {return glGetUniformLocation(m_ProgramID, "View_Proj");};

        /**
         * @brief Get the location of the model uniform
         *
         * @return GLuint Location ID for the model uniform
         */
        GLuint getModelLoc() {return glGetUniformLocation(m_ProgramID, "Model");};

};

#endif // GAME_PROGRAM_HPP__
