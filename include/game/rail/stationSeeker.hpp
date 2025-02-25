#ifndef INCLUDE_GAME_RAIL_STATIONSEEKER_HPP_
#define INCLUDE_GAME_RAIL_STATIONSEEKER_HPP_

#include "game/rail/railWalker.hpp"
#include "framework/geometry/rectangleObject.hpp"

enum seeker_state{AT_STATION, MOVING};

class StationSeeker : public RailWalker {
 public:
  StationSeeker(Vector2D start_position, std::shared_ptr<RailPiece> piece, std::shared_ptr<RailConnection> connection);

  void Update(float distance_travelled, bool train_at_station);

  glm::mat4 CalculateSeekerMatrix();

  std::shared_ptr<RectangleObject> objectGet() { return m_seeker_object; }

 private:
  seeker_state m_state = MOVING;
  glm::mat4 m_seeker_matrix;
  std::shared_ptr<RectangleObject> m_seeker_object;
  Vector2D m_seeker_position;
};

#endif /* INCLUDE_GAME_RAIL_STATIONSEEKER_HPP_ */
