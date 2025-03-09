#include "game/rail/railConnection.hpp"
#include "game/rail/railPiece.hpp"
#include "game/rail/straightRailPiece.hpp"

#include <gtest/gtest.h>

TEST(RailConnectionTest, RailConnection_add_connection_valid) {
    int ret;

    RailConnection connection;

    std::shared_ptr<StraightRailPiece> rail_a = std::make_shared<StraightRailPiece>();
    std::shared_ptr<StraightRailPiece> rail_b = std::make_shared<StraightRailPiece>();

    ret = connection.AddConnection(rail_a);
    EXPECT_EQ(ret, 0);

    ret = connection.AddConnection(rail_b);
    EXPECT_EQ(ret, 0);
}

TEST(RailConnectionTest, RailConnection_add_connection_invalid_nullptr) {
    int ret;

    RailConnection connection;

    ret = connection.AddConnection(nullptr);
    EXPECT_EQ(ret, -1);
}

TEST(RailConnectionTest, RailConnection_add_connection_invalid_same_ptr) {
    int ret;

    RailConnection connection;

    std::shared_ptr<StraightRailPiece> rail_a = std::make_shared<StraightRailPiece>();

    ret = connection.AddConnection(rail_a);
    EXPECT_EQ(ret, 0);

    ret = connection.AddConnection(rail_a);
    EXPECT_EQ(ret, -1);
}

TEST(RailConnectionTest, RailConnection_add_connection_valid_full) {
    int ret;

    RailConnection connection;

    std::shared_ptr<StraightRailPiece> rail_a = std::make_shared<StraightRailPiece>();
    std::shared_ptr<StraightRailPiece> rail_b = std::make_shared<StraightRailPiece>();
    std::shared_ptr<StraightRailPiece> rail_c = std::make_shared<StraightRailPiece>();

    ret = connection.AddConnection(rail_a);
    EXPECT_EQ(ret, 0);

    ret = connection.AddConnection(rail_b);
    EXPECT_EQ(ret, 0);

    ret = connection.AddConnection(rail_c);
    EXPECT_EQ(ret, -1);
}

TEST(RailConnectionTest, RailConnection_next_rail_piece_get_valid) {
    int ret;
    std::shared_ptr<RailPiece> next_rail_piece;

    RailConnection connection;

    std::shared_ptr<StraightRailPiece> rail_a = std::make_shared<StraightRailPiece>();
    std::shared_ptr<StraightRailPiece> rail_b = std::make_shared<StraightRailPiece>();

    ret = connection.AddConnection(rail_a);
    EXPECT_EQ(ret, 0);

    ret = connection.AddConnection(rail_b);
    EXPECT_EQ(ret, 0);

    ret = connection.nextRailPieceGet(rail_a, next_rail_piece);
    EXPECT_EQ(ret, 0);
    EXPECT_EQ(next_rail_piece, rail_b);

    ret = connection.nextRailPieceGet(rail_b, next_rail_piece);
    EXPECT_EQ(ret, 0);
    EXPECT_EQ(next_rail_piece, rail_a);
}

TEST(RailConnectionTest, RailConnection_next_rail_piece_get_invalid_nullptr) {
    int ret;
    std::shared_ptr<RailPiece> next_rail_piece;

    RailConnection connection;

    std::shared_ptr<StraightRailPiece> rail_a = std::make_shared<StraightRailPiece>();
    std::shared_ptr<StraightRailPiece> rail_b = std::make_shared<StraightRailPiece>();

    ret = connection.AddConnection(rail_a);
    EXPECT_EQ(ret, 0);

    ret = connection.AddConnection(rail_b);
    EXPECT_EQ(ret, 0);

    ret = connection.nextRailPieceGet(nullptr, next_rail_piece);
    EXPECT_EQ(ret, -2);
}

TEST(RailConnectionTest, RailConnection_next_rail_piece_get_valid_only_one_connection) {
    int ret;
    std::shared_ptr<RailPiece> next_rail_piece;

    RailConnection connection;

    std::shared_ptr<StraightRailPiece> rail_a = std::make_shared<StraightRailPiece>();
    std::shared_ptr<StraightRailPiece> rail_b = std::make_shared<StraightRailPiece>();

    ret = connection.AddConnection(rail_a);
    EXPECT_EQ(ret, 0);

    ret = connection.nextRailPieceGet(rail_a, next_rail_piece);
    EXPECT_EQ(ret, -1);
}