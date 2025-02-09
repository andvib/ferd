#ifndef INCLUDE_GAME_RAIL_RAILCONNECTION_HPP_
#define INCLUDE_GAME_RAIL_RAILCONNECTION_HPP_

#include <memory>
#include <tuple>

#include "game/rail/railPiece.hpp"

class RailConnection {
 public:
  explicit RailConnection(Vector2D position) : m_position(position) {}

  void AddConnectionA(std::shared_ptr<RailPiece> rail_piece,
                      std::shared_ptr<RailConnection> rail_connection);
  void AddConnectionB(std::shared_ptr<RailPiece> rail_piece,
                      std::shared_ptr<RailConnection> rail_connection);

  std::tuple<std::shared_ptr<RailPiece>, bool> getRailA();
  std::tuple<std::shared_ptr<RailConnection>, bool> getConnectionA();

  std::tuple<std::shared_ptr<RailPiece>, bool> getRailB();
  std::tuple<std::shared_ptr<RailConnection>, bool> getConnectionB();

  Vector2D getPos() const { return m_position; }

 private:
  std::shared_ptr<RailPiece> m_rail_A;
  std::shared_ptr<RailPiece> m_rail_B;

  std::shared_ptr<RailConnection> m_connection_A = nullptr;
  std::shared_ptr<RailConnection> m_connection_B = nullptr;

  Vector2D m_position;
};

#endif /* INCLUDE_GAME_RAIL_RAILCONNECTION_HPP_ */
