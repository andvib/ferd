#ifndef INCLUDE_FRAMEWORK_GRAPHICSFRAMEWORK_HPP_
#define INCLUDE_FRAMEWORK_GRAPHICSFRAMEWORK_HPP_

#include <vector>

#include "framework/geometry/lineObject.hpp"
#include "framework/geometry/rectangleObject.hpp"
#include "framework/graphicsProgram.hpp"
#include "framework/windowHandler.hpp"
#include "game/camera.hpp"
#include "game/world.hpp"

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
  int Activate();

  /**
   * @brief Add shaders to use to render trains
   *
   * @details Compiles and attaches the shaders to the train program
   *
   * @param vertex_filepath Filepath to the vertex shader
   * @param fragment_filepath Filepath to the fragment shader
   */
  void AddTrainShader(const char *vertex_filepath,
                      const char *fragment_filepath);

  /**
   * @brief Add shaders that will render lines
   *
   * @details Compiles and attaches the shaders to the train program
   *
   * @param vertex_filepath Filepath to the vertex shader
   * @param fragment_filepath Filepath to the fragment shader
   */
  void AddLineShader(const char *vertex_filepath,
                     const char *fragment_filepath);

  /**
   * @brief Add world object to the framework
   *
   * @param world World object
   */
  void AddWorld(World *world) { p_World = world; }

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
   *
   * @param delta_time_ms Time since previous frame, in milliseconds
   */
  void Update(clock_t delta_time_ms);

  /**
   * @brief Render objects to the frame buffer
   */
  void Render();

  /**
   * @brief Swap to the staged frame buffer
   */
  void swapBuffers();

  /**
   * @brief Select the current camera in use
   *
   * @param camera Pointer to Camera object in use
   */
  void addCamera(Camera *camera) { p_Camera = camera; }

 private:
  GraphicsProgram *m_TrainProgram;
  GraphicsProgram *m_LineProgram;
  WindowHandler *m_Window;
  World *p_World;
  Camera *p_Camera;
};

#endif /* INCLUDE_FRAMEWORK_GRAPHICSFRAMEWORK_HPP_ */
