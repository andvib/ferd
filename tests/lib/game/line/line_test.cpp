#include "game/line.hpp"

#include <gtest/gtest.h>

#include "MockOpenGLWrapper.h"
#include "framework/ferd_color.hpp"
#include "game/waypoint/station.hpp"
#include "game/waypoint/waypoint.hpp"

TEST(LineTest, LineTest_init) {
  auto mockOpenGL = std::make_shared<MockOpenGLWrapper>();

  Station test_wp1({100, -100}, mockOpenGL);
  Station test_wp2({100, -40}, mockOpenGL);
  Waypoint test_wp3({100, -5});
  Station test_wp4({80, 35}, mockOpenGL);
  Waypoint test_wp5({20, 30});
  Station test_wp6({-30, 50}, mockOpenGL);

  std::vector<Waypoint *> wp_vector = {&test_wp1, &test_wp2, &test_wp3,
                                       &test_wp4, &test_wp5, &test_wp6};

  Line test_line(wp_vector, FERD_COLOR_1, mockOpenGL);

  EXPECT_EQ(wp_vector.size(), test_line.NumberOfStations());
}
