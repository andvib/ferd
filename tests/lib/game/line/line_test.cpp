#include "game/line.hpp"

#include <gtest/gtest.h>

#include <memory>
#include <vector>

#include "MockOpenGLWrapper.h"
#include "framework/ferd_color.hpp"
#include "game/waypoint/station.hpp"
#include "game/waypoint/waypoint.hpp"

using ::testing::NiceMock;

TEST(LineTest, LineTest_init) {
  auto mockOpenGL = std::make_shared<NiceMock<MockOpenGLWrapper>>();

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

TEST(LineTest, LineTest_getNextWaypoint_valid) {
  auto mockOpenGL = std::make_shared<NiceMock<MockOpenGLWrapper>>();

  Station test_wp1({100, -100}, mockOpenGL);
  Waypoint test_wp2({200, -5});
  Station test_wp3({300, 300}, mockOpenGL);

  std::vector<Waypoint *> wp_vector = {&test_wp1, &test_wp2, &test_wp3};
  Line test_line(wp_vector, FERD_COLOR_1, mockOpenGL);
  line_ctx line_context = {
      .index = 0,
      .direction = LineDirection::FORWARD,
  };
  position_t next_waypoint;

  int err = test_line.GetNextWaypoint(&next_waypoint, line_context);

  EXPECT_EQ(err, 0);
  EXPECT_EQ(next_waypoint.x, 200);
  EXPECT_EQ(next_waypoint.y, -5);
}

TEST(LineTest, LineTest_getNextWaypoint_invalid_bad_index) {
  auto mockOpenGL = std::make_shared<NiceMock<MockOpenGLWrapper>>();

  Station test_wp1({0, 0}, mockOpenGL);
  Waypoint test_wp2({200, -50});
  Station test_wp3({300, 400}, mockOpenGL);

  std::vector<Waypoint *> wp_vector = {&test_wp1, &test_wp2, &test_wp3};
  Line test_line(wp_vector, FERD_COLOR_1, mockOpenGL);
  line_ctx line_context = {
      .index = 2,
      .direction = LineDirection::FORWARD,
  };

  int err;
  position_t next_waypoint;

  err = test_line.GetNextWaypoint(&next_waypoint, line_context);
  EXPECT_EQ(err, -1);

  line_context.index = 0;
  line_context.direction = LineDirection::BACKWARD;

  err = test_line.GetNextWaypoint(&next_waypoint, line_context);
  EXPECT_EQ(err, -1);
}

TEST(LineTest, LineTest_getNextWaypoint_invalid_null_ptr) {
  auto mockOpenGL = std::make_shared<NiceMock<MockOpenGLWrapper>>();

  Station test_wp1({100, -300}, mockOpenGL);
  Waypoint test_wp2({200, -5});
  Station test_wp3({500, 300}, mockOpenGL);

  std::vector<Waypoint *> wp_vector = {&test_wp1, &test_wp2, &test_wp3};
  Line test_line(wp_vector, FERD_COLOR_1, mockOpenGL);
  line_ctx line_context = {
      .index = 0,
      .direction = LineDirection::FORWARD,
  };

  int err;

  err = test_line.GetNextWaypoint(nullptr, line_context);
  EXPECT_EQ(err, -1);
}

TEST(LineTest, LineTest_getNextStation_valid) {
  auto mockOpenGL = std::make_shared<NiceMock<MockOpenGLWrapper>>();

  Station test_wp1({0, 0}, mockOpenGL);
  Waypoint test_wp2({3, 4});
  Waypoint test_wp3({0, 8});
  Station test_wp4({6, 16}, mockOpenGL);
  Waypoint test_wp5({3, 12});

  std::vector<Waypoint *> wp_vector = {&test_wp1, &test_wp2, &test_wp3,
                                       &test_wp4, &test_wp5};
  Line test_line(wp_vector, FERD_COLOR_1, mockOpenGL);
  line_ctx line_context = {
      .index = 0,
      .direction = LineDirection::FORWARD,
  };

  position_t station;
  int ret = test_line.GetNextStation(&station, line_context);
  EXPECT_EQ(ret, 0);
  EXPECT_EQ(station.x, 6);
  EXPECT_EQ(station.y, 16);

  line_context.index = 2;
  line_context.direction = LineDirection::BACKWARD;

  ret = test_line.GetNextStation(&station, line_context);
  EXPECT_EQ(ret, 0);
  EXPECT_EQ(station.x, 0);
  EXPECT_EQ(station.y, 0);
}

TEST(LineTest, LineTest_getNextStation_invalid_bad_index) {
  auto mockOpenGL = std::make_shared<NiceMock<MockOpenGLWrapper>>();

  Station test_wp1({0, -100}, mockOpenGL);
  Waypoint test_wp2({400, -5});
  Station test_wp3({200, 300}, mockOpenGL);

  std::vector<Waypoint *> wp_vector = {&test_wp1, &test_wp2, &test_wp3};
  Line test_line(wp_vector, FERD_COLOR_1, mockOpenGL);
  line_ctx line_context = {
      .index = 2,
      .direction = LineDirection::FORWARD,
  };
  position_t next_waypoint;
  int err;

  err = test_line.GetNextStation(&next_waypoint, line_context);
  EXPECT_EQ(err, -1);

  line_context.index = 0;
  line_context.direction = LineDirection::BACKWARD;

  err = test_line.GetNextStation(&next_waypoint, line_context);
  EXPECT_EQ(err, -1);
}

TEST(LineTest, LineTest_getNextStation_invalid_null_ptr) {
  auto mockOpenGL = std::make_shared<NiceMock<MockOpenGLWrapper>>();

  Station test_wp1({-100, -100}, mockOpenGL);
  Waypoint test_wp2({-50, -50});
  Station test_wp3({400, 400}, mockOpenGL);

  std::vector<Waypoint *> wp_vector = {&test_wp1, &test_wp2, &test_wp3};
  Line test_line(wp_vector, FERD_COLOR_1, mockOpenGL);
  line_ctx line_context = {
      .index = 0,
      .direction = LineDirection::FORWARD,
  };

  int err;

  err = test_line.GetNextStation(nullptr, line_context);
  EXPECT_EQ(err, -1);
}

TEST(LineTest, LineTest_getNextWaypointDistance_valid) {
  auto mockOpenGL = std::make_shared<NiceMock<MockOpenGLWrapper>>();

  Station test_wp1({0, 0}, mockOpenGL);
  Waypoint test_wp2({3, 4});

  std::vector<Waypoint *> wp_vector = {&test_wp1, &test_wp2};
  Line test_line(wp_vector, FERD_COLOR_1, mockOpenGL);
  line_ctx line_context = {
      .index = 0,
      .direction = LineDirection::FORWARD,
  };

  int distance = test_line.GetNextWaypointDistance(line_context, {0, 0});
  EXPECT_EQ(distance, 5);
}

TEST(LineTest, LineTest_GetNextSationDistance_valid) {
  auto mockOpenGL = std::make_shared<NiceMock<MockOpenGLWrapper>>();

  Station test_wp1({0, 0}, mockOpenGL);
  Waypoint test_wp2({3, 4});
  Waypoint test_wp3({0, 8});
  Waypoint test_wp4({3, 12});
  Station test_wp5({6, 16}, mockOpenGL);

  std::vector<Waypoint *> wp_vector = {&test_wp1, &test_wp2, &test_wp3,
                                       &test_wp4, &test_wp5};
  Line test_line(wp_vector, FERD_COLOR_1, mockOpenGL);
  line_ctx line_context = {
      .index = 0,
      .direction = LineDirection::FORWARD,
  };

  float distance = test_line.GetNextStationDistance(line_context, {0, 0});
  EXPECT_EQ(distance, 20);
}

TEST(LineTest, LineTest_GetNextStationDistance_invalid_no_station) {
  auto mockOpenGL = std::make_shared<NiceMock<MockOpenGLWrapper>>();

  Waypoint test_wp1({0, 0});
  Waypoint test_wp2({3, 4});
  Waypoint test_wp3({0, 8});

  std::vector<Waypoint *> wp_vector = {&test_wp1, &test_wp2, &test_wp3};
  Line test_line(wp_vector, FERD_COLOR_1, mockOpenGL);
  line_ctx line_context = {
      .index = 0,
      .direction = LineDirection::FORWARD,
  };

  float distance = test_line.GetNextStationDistance(line_context, {0, 0});
  EXPECT_EQ(distance, -1);

  line_ctx line_context2 = {
      .index = 2,
      .direction = LineDirection::BACKWARD,
  };

  distance = test_line.GetNextStationDistance(line_context2, {0, 0});
  EXPECT_EQ(distance, -1);
}
