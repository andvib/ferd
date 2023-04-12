#ifndef FRAMEWORK_HPP__
#define FRAMEWORK_HPP__

#include "graphicsProgram.hpp"
#include "windowHandler.hpp"
#include "graphicsScreen.hpp"
#include "game/camera.hpp"
#include "game/rectangleObject.hpp"

#include <vector>

class GraphicsFramework {

    public:
        GraphicsFramework();
        ~GraphicsFramework();
        
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

        /**
         * @brief Update screen buffer for new frame
         *
         * @details Prepares the camera for a new frame
         */
        void update();

        /**
         * @brief Render objects to the frame buffer
         */
        void render();

        /**
         * @brief Swap to the staged frame buffer
         */
        void swapBuffers();

        /**
         * @brief Select the current camera in use
         *
         * @param camera Pointer to Camera object in use
         */
        void addCamera(Camera *camera) {p_Camera = camera;};

        /**
         * @brief Add a render object to the framework
         *
         * @param object
         */
        void addRenderObject(RectangleObject *object) { v_objects.push_back(object); };

    private:
        GraphicsProgram *m_Program;
        WindowHandler *m_Window;
        GraphicsScreen *m_Screen;
        Camera *p_Camera;
        std::vector<RectangleObject*> v_objects;
};

#endif /* FRAMEWORK_HPP__ */
