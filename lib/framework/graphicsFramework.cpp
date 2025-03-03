#include "framework/graphicsFramework.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "spdlog/spdlog.h"

GraphicsFramework::GraphicsFramework() {
  srand(static_cast<unsigned>(time(0)));
}

int GraphicsFramework::Activate() {
  /* Initialize the library */
  glewExperimental = GL_TRUE;
  if (!glfwInit()) {
    spdlog::critical("Failed to initalize GLFW");
  }
  spdlog::info("GLFW initialized");

  m_Window->activate();
  glfwSwapInterval(1);
  glEnable(GL_MULTISAMPLE);

  if (glewInit() != GLEW_OK) {
    spdlog::critical("Failed to initialize glew");
  }
  spdlog::info("GLEW initialized");

  m_TrainProgram->Create();
  m_LineProgram->Create();
  m_StationProgram->Create();

  return 0;
}

void AttachShader(GraphicsProgram *program, const char *vertex_file_path,
                  const char *fragment_file_path) {
  VertexShader verShader;
  verShader.loadShader(vertex_file_path);
  verShader.compileShader();

  FragmentShader fragShader;
  fragShader.loadShader(fragment_file_path);
  fragShader.compileShader();

  program->AttachShaders(verShader, fragShader);

  verShader.deleteShader();
  fragShader.deleteShader();
}

void GraphicsFramework::AddTrainShader(const char *vertex_file_path,
                                       const char *fragment_file_path) const {
  AttachShader(m_TrainProgram.get(), vertex_file_path, fragment_file_path);
}

void GraphicsFramework::AddLineShader(const char *vertex_file_path,
                                      const char *fragment_file_path) const {
  AttachShader(m_LineProgram.get(), vertex_file_path, fragment_file_path);
}

void GraphicsFramework::AddStationShader(const char *vertex_file_path,
                                         const char *fragment_file_path) const {
  AttachShader(m_StationProgram.get(), vertex_file_path, fragment_file_path);
}

bool GraphicsFramework::isRunning() { return m_Window->isWindowRunning(); }

void GraphicsFramework::terminate() { glfwTerminate(); }

void GraphicsFramework::Update(clock_t delta_time_ms) {
  glClearColor((245.0 / 255), (245.0 / 255), (220.0 / 255), 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  m_Window->updateCamera(p_Camera);
  m_Window->update();

  p_World->Update(delta_time_ms);
}

void GraphicsFramework::Render() {
  glm::mat4 vp = p_Camera->calculateViewProjMatrix();

  m_LineProgram->EnableProgram();
  glUniformMatrix4fv(
      glGetUniformLocation(m_LineProgram->get_program_id(), "View_Proj"), 1,
      GL_FALSE, &vp[0][0]);
  p_World->RenderLineObjects();

  m_StationProgram->EnableProgram();
  glUniformMatrix4fv(
      glGetUniformLocation(m_StationProgram->get_program_id(), "View_Proj"), 1,
      GL_FALSE, &vp[0][0]);
  p_World->RenderStations(
      glGetUniformLocation(m_StationProgram->get_program_id(), "Model"));

  m_TrainProgram->EnableProgram();
  glUniformMatrix4fv(
      glGetUniformLocation(m_TrainProgram->get_program_id(), "View_Proj"), 1,
      GL_FALSE, &vp[0][0]);

  p_World->RenderRectangles(
      glGetUniformLocation(m_TrainProgram->get_program_id(), "Model"));

  m_Window->render();
}

void GraphicsFramework::swapBuffers() { m_Window->swapBuffers(); }
