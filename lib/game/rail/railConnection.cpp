#include "game/rail/railConnection.hpp"

#include <spdlog/spdlog.h>

#include <memory>
#include <tuple>

#include "game/rail/railPiece.hpp"

void RailConnection::AddConnectionA(std::shared_ptr<RailPiece> rail_piece,
                                    std::shared_ptr<RailConnection> rail_connection) {
    m_rail_A = rail_piece;
    m_connection_A = rail_connection;
}

void RailConnection::AddConnectionB(std::shared_ptr<RailPiece> rail_piece,
                                    std::shared_ptr<RailConnection> rail_connection) {
    m_rail_B = rail_piece;
    m_connection_B = rail_connection;
}


std::tuple<std::shared_ptr<RailPiece>, bool> RailConnection::getRailA() {
    if (m_rail_A) {
        return {m_rail_A, false};
    } else {
        return {m_rail_B, true};
    }
}

std::tuple<std::shared_ptr<RailConnection>, bool> RailConnection::getConnectionA() {
    if (m_connection_A) {
        return {m_connection_A, false};
    } else {
        return {m_connection_B, true};
    }
}

std::tuple<std::shared_ptr<RailPiece>, bool> RailConnection::getRailB() {
    if (m_rail_B) {
        return {m_rail_B, false};
    } else {
        return {m_rail_A, true};
    }
}

std::tuple<std::shared_ptr<RailConnection>, bool> RailConnection::getConnectionB() {
    if (m_connection_B) {
        return {m_connection_B, false};
    } else {
        return {m_connection_A, true};
    }
}
