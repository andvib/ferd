#ifndef WINDOW_HANDLER_HPP__
#define WINDOW_HANDLER_HPP__

#include <GLFW/glfw3.h>

class WindowHandler {

    private:
        /* Variable holding the GLFW ID of the window */
        GLFWwindow* window;

    public:
        /**
         * @brief Construct a new Window Handler:: Window Handler object
         *
         * @details Sets window hints for GLFW
         */
        WindowHandler();

        /**
         * @brief Activate the window
         *
         * @details Creates a window from GLFW, and makes it the current context. Also sets the input mode
         *          for the window.
         *
         * @return int 0 if success, negative value otherwise
         */
        int activate();

        /**
         * @brief Swap the OpenGL Buffers for the window
         *
         * @details activate() must have been called for the window before calling swapBuffers().
         *          Also instructs GLFW to process events.
         *
         * @return int 0 if success, negative if window has not been activated
         */
        int swapBuffers();

        /**
         * @brief Checks if user has closed window
         *
         * @details Checks if the user has pressed either escape button, or crossed out the window.
         *
         * @return true Window has not been closed by user and is running
         * @return false Window has been closed by user
         */
        bool isWindowRunning();

        GLFWwindow* getWindow(){return window;};
};

#endif /* WINDOW_HANDLER_HPP__ */
