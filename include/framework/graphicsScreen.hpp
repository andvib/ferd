#ifndef INCLUDE_FRAMEWORK_GRAPHICSSCREEN_HPP_
#define INCLUDE_FRAMEWORK_GRAPHICSSCREEN_HPP_

#include <GL/glew.h>

class GraphicsScreen {
 public:
  GraphicsScreen() {}

  /**
   * @brief Update the screen for a new buffer
   *
   * @details Sets the GL clear attributes and selects the GL program
   *
   * @param ProgramID ID of the GL program to be used
   */
  void Update(GLuint ProgramID);
};

#endif /* INCLUDE_FRAMEWORK_GRAPHICSSCREEN_HPP_ */
