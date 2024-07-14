#ifndef INCLUDE_FRAMEWORK_WINDOWHANDLER_HPP_
#define INCLUDE_FRAMEWORK_WINDOWHANDLER_HPP_

#include <GLFW/glfw3.h>

#include "game/camera.hpp"

class WindowHandler {
 private:
  /* Variable holding the GLFW ID of the window */
  GLFWwindow* window;

 public:
  /**
   * @brief Activate the window
   *
   * @details Creates a window from GLFW, and makes it the current context. Also
   * sets the input mode for the window and window hints.
   *
   * @return int 0 if success, negative value otherwise
   */
  int activate();

  /**
   * @brief Swap the OpenGL Buffers for the window
   *
   * @details activate() must have been called for the window before calling
   * swapBuffers(). Also instructs GLFW to process events.
   *
   * @return int 0 if success, negative if window has not been activated
   */
  int swapBuffers();

  /**
   * @brief Checks if user has closed window
   *
   * @details Checks if the user has pressed either escape button, or crossed
   * out the window.
   *
   * @return true Window has not been closed by user and is running
   * @return false Window has been closed by user
   */
  bool isWindowRunning();

  /**
   * @brief Updates camera movement base on user input
   *
   * @details Calls the camera move functions based on the user keyboard input.
   *
   * @param gameCamera
   */
  void updateCamera(Camera* gameCamera);

  /**
   * @brief Update the window attributes
   *
   * @details Fetches IO events and updates the GUI
   */
  void update();

  /**
   * @brief Render the GUI objects
   */
  void render();
};

#endif /* INCLUDE_FRAMEWORK_WINDOWHANDLER_HPP_ */
