#ifndef INCLUDE_FRAMEWORK_GAMESHADER_HPP_
#define INCLUDE_FRAMEWORK_GAMESHADER_HPP_

#include <string>

class GameShader {
 private:
  GLuint shaderID;

 public:
  /* The shader code read from file */
  std::string shaderCode;

  /**
   * @brief Construct a new Game Shader object
   */
  GameShader();

  /**
   * @brief Construct a new Game Shader object with a give shader ID
   *
   * @param shader_id Shader ID as returned by glCreateShader
   */
  explicit GameShader(GLuint shader_id);

  /**
   * @brief Load the shader code from file
   *
   * @details Reads the shader code from file and stores it in shaderCode
   *
   * @param file_path File containing shader code
   * @return int 0 if file is succsessfully read, -1 if file can not be opened
   */
  int loadShader(const char *file_path);

  /**
   * @brief Compiles the shader read from code
   *
   * @return int 0 if compilation was successfull, -1 otherwise
   */
  int compileShader();

  /**
   * @brief Get the Shader ID object
   *
   * @return GLuint Shader ID
   */
  GLuint getShaderID();

  /**
   * @brief Deletes the shader from GL context
   *
   * @details Use this to free up space. Can safely be done after shader has
   * been compiled.
   */
  void deleteShader();
};

class VertexShader : public GameShader {
 public:
  /**
   * @brief Construct a new Vertex Shader object
   */
  VertexShader() : GameShader(glCreateShader(GL_VERTEX_SHADER)) {}
};

class FragmentShader : public GameShader {
 public:
  /**
   * @brief Construct a new Fragment Shader object
   */
  FragmentShader() : GameShader(glCreateShader(GL_FRAGMENT_SHADER)) {}
};

#endif /* INCLUDE_FRAMEWORK_GAMESHADER_HPP_ */
