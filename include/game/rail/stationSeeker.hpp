#ifndef INCLUDE_GAME_RAIL_STATIONSEEKER_HPP_
#define INCLUDE_GAME_RAIL_STATIONSEEKER_HPP_

#include <memory>

#include "framework/geometry/rectangleObject.hpp"
#include "game/rail/railWalker.hpp"

enum class SeekerState { AT_STATION, MOVING };

enum class SeekerEvent { NO_EVENT, ARRIVED_AT_STATION };

class StationSeeker : public RailWalker {
 public:
  StationSeeker(Vector2D start_position, std::shared_ptr<RailPiece> piece,
                std::shared_ptr<RailConnection> connection);

  SeekerEvent Update(float distance_travelled, bool train_at_station);

  glm::mat4 CalculateSeekerMatrix();

  std::shared_ptr<RectangleObject> objectGet() const { return m_seeker_object; }

  void visualAssetSet(std::shared_ptr<RectangleObject> asset_ptr) {
    m_visual_asset = asset_ptr;
  }

 private:
  SeekerState m_state = SeekerState::MOVING;
  glm::mat4 m_seeker_matrix;
  std::shared_ptr<RectangleObject> m_seeker_object;
  Vector2D m_seeker_position;
  std::shared_ptr<RectangleObject> m_visual_asset;
};

#endif /* INCLUDE_GAME_RAIL_STATIONSEEKER_HPP_ */
