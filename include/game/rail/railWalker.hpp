#ifndef INCLUDE_GAME_RAIL_RAILWALKER_HPP_
#define INCLUDE_GAME_RAIL_RAILWALKER_HPP_

#include <memory>

#include "game/physics/kinematics.hpp"
#include "game/rail/railPiece.hpp"
#include "game/rail/railConnection.hpp"

class RailWalker {
 public:
  RailWalker() = default;

  Vector2D nextPositionGet(Vector2D current_position, float distance_travelled);

  Vector2D rotationGet(Vector2D current_position);

  void set_current_rail(std::shared_ptr<RailPiece> piece) {current_rail = piece;}
  void set_next_connection(std::shared_ptr<RailConnection> new_connection)
                                                    { connection = new_connection; }

 private:
  std::shared_ptr<RailPiece> current_rail;
  std::shared_ptr<RailConnection> connection;
  RailDirection m_direction = RailDirection::RAIL_DIRECTION_A_TO_B;
  int m_skip_frame_counter = 0;
};

#endif /* INCLUDE_GAME_RAIL_RAILWALKER_HPP_ */
