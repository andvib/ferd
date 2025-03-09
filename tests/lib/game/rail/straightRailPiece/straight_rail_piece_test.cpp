#include "game/rail/railPiece.hpp"
#include "game/rail/straightRailPiece.hpp"

#include <gtest/gtest.h>

TEST(StraightRailPieceTest, StraightRailPiece_add_waypoint_valid) {
    int ret;

    StraightRailPiece rail_piece;

    Waypoint test_wp1({100, -100});
    Waypoint test_wp2({100, 200});

    ret = rail_piece.waypointsSet(&test_wp1, &test_wp2);
    EXPECT_EQ(ret, 0);

}

TEST(StraightRailPieceTest, StraightRailPiece_add_waypoint_invalid_nullptr) {
    int ret;

    StraightRailPiece rail_piece;

    Waypoint test_wp1({100, -100});
    Waypoint test_wp2({100, 200});

    ret = rail_piece.waypointsSet(NULL, &test_wp2);
    EXPECT_EQ(ret, -1);

    ret = rail_piece.waypointsSet(&test_wp1, NULL);
    EXPECT_EQ(ret, -1);
}

TEST(StraightRailPieceTest, StraightRailPiece_add_waypoint_invalid_same_position) {
    int ret;

    Waypoint test_wp1({100, -100});
    Waypoint test_wp2({100, -100});

    StraightRailPiece rail_piece;

    ret = rail_piece.waypointsSet(&test_wp1, &test_wp2);
    EXPECT_EQ(ret, -1);
}

TEST(StraightRailPieceTest, StraightRailPiece_add_waypoint_invalid_same_ptr) {
    int ret;

    Waypoint test_wp1({100, -100});

    StraightRailPiece rail_piece;

    ret = rail_piece.waypointsSet(&test_wp1, &test_wp1);
    EXPECT_EQ(ret, -1);
}

TEST(StraightRailPieceTest, StraightRailPiece_position_on_rail_get_valid) {
    int ret;
    Vector2D position_on_rail;

    Waypoint test_wp1({0,0});
    Waypoint test_wp2({10,0});

    StraightRailPiece rail_piece;

    ret = rail_piece.waypointsSet(&test_wp1, &test_wp2);
    EXPECT_EQ(ret, 0);

    position_on_rail = rail_piece.PositionOnRailGet({1,0}, 5.f, RailDirection::RAIL_DIRECTION_A_TO_B);
    EXPECT_TRUE(position_on_rail == Vector2D(6, 0));

    position_on_rail = rail_piece.PositionOnRailGet({8,0}, 4.f, RailDirection::RAIL_DIRECTION_B_TO_A);
    EXPECT_TRUE(position_on_rail == (Vector2D(4, 0)));

}

TEST(StraightRailPieceTest, StraightRailPiece_orientation_on_rail_get_valid) {
    int ret;
    Vector2D orientation_on_rail;

    Waypoint test_wp1({0,0});
    Waypoint test_wp2({6,8});

    StraightRailPiece rail_piece;

    ret = rail_piece.waypointsSet(&test_wp1, &test_wp2);
    EXPECT_EQ(ret, 0);

    orientation_on_rail = rail_piece.OrientationOnRailGet({0,0}, RailDirection::RAIL_DIRECTION_A_TO_B);
    EXPECT_EQ(orientation_on_rail, Vector2D(0.6, 0.8));

    orientation_on_rail = rail_piece.OrientationOnRailGet({0,0}, RailDirection::RAIL_DIRECTION_B_TO_A);
    EXPECT_EQ(orientation_on_rail, Vector2D(-0.6, -0.8));
}

TEST(StraightRailPieceTest, StraightRailPiece_total_length_get_valid) {
    int ret;
    float length;

    Waypoint test_wp1({0,0});
    Waypoint test_wp2({0,8});

    StraightRailPiece rail_piece;

    ret = rail_piece.waypointsSet(&test_wp1, &test_wp2);
    EXPECT_EQ(ret, 0);

    length = rail_piece.TotalLengthGet();
    EXPECT_EQ(length, 8);
}
