#ifndef FRAMEWORK_HPP__
#define FRAMEWORK_HPP__

#include "graphicsProgram.hpp"
#include "windowHandler.hpp"


class GraphicsFramework {

    public:
        WindowHandler Window;
        GraphicsProgram Program;

        /**
         * @brief Construct a new Graphics Framework object
         */
        GraphicsFramework() {};
        
        /**
         * @brief Activate the framework
         *
         * @details Activates all libaries required to run the framework. Must only be
         *          executed once in the entire application.
         *  
         * @return int 0 on success
         */
        int activate();

        /**
         * @brief Add shaders to the framework
         *
         * @details Compiles and attaches the shaders to the framework. Only one pair of shaders
         *          can be used in the current program.
         *
         * @param vertex_filepath Filepath to the vertex shader
         * @param fragment_filepath Filepath to the fragment shader
         */
        void addShaders(const char *vertex_filepath, const char *fragment_filepath);
        
        /**
         * @brief Checks if the Framework has been closed
         *
         * @details Checks if the user has closed the window
         *
         * @return true Framework should continue to run
         * @return false Framework should be closed
         */
        bool isRunning();

        /**
         * @brief Terminate the Framework session
         */
        void terminate();
};

#endif /* FRAMEWORK_HPP__ */
