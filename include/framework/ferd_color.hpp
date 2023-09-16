#ifndef INCLUDE_FRAMEWORK_FERD_COLOR_HPP_
#define INCLUDE_FRAMEWORK_FERD_COLOR_HPP_

#include <GL/glew.h>

struct ferd_color {
  GLfloat red;
  GLfloat green;
  GLfloat blue;
};

const struct ferd_color FERD_COLOR_1 = {0, 0.25, 0.75};
const struct ferd_color FERD_COLOR_2 = {0, 0.75, 1};
const struct ferd_color FERD_COLOR_3 = {0, 0.75, 0.5};
const struct ferd_color FERD_COLOR_4 = {0, 0.8, 0.75};
const struct ferd_color FERD_COLOR_5 = {0, 0.5, 0.9};

#endif /* INCLUDE_FRAMEWORK_FERD_COLOR_HPP_ */
