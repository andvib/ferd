#ifndef INCLUDE_GAME_TRAIN_HPP_
#define INCLUDE_GAME_TRAIN_HPP_

#include <chrono>
#include <memory>

#include "framework/ferd_color.hpp"
#include "framework/geometry/rectangleObject.hpp"
#include "game/line.hpp"
#include "game/physics/kinematics.hpp"
#include "game/trainNavigator.hpp"
#include "game/trainPhysics.hpp"
#include "game/rail/railWalker.hpp"
#include "game/rail/stationSeeker.hpp"

enum train_state { STOPPED_AT_STATION, ENROUTE, APPROACH };

class Train {
 public:
  //Train();
  ~Train();

  /**
   * @brief Construct a new Train object
   *
   * @param line Line object the train will be traveling along
   * @param start_position Start position of the train
   * @param acceleration Acceleration of the train
   * @param color Color struct for the color of the train
   */
  Train(Line* line, Vector2D start_position, float acceleration,
        const struct ferd_color color);
  Train(Vector2D start_position, const struct ferd_color color, std::shared_ptr<RailPiece> piece, std::shared_ptr<RailConnection> connection);

  /**
   * @brief Update the state machine and physics model of the train, and
   * navigate the route
   *
   * @param delta_time_ms Time since previous update, in milliseconds
   */
  void Update(clock_t delta_time_ms);

  /**
   * @brief Set the visual asset associated with the train
   *
   * @param asset_ptr   Pointer to the asset object
   */
  void visualAssetSet(std::shared_ptr<RectangleObject> asset_ptr) { m_visual_asset = asset_ptr; }
  void visualSeekerSet(std::shared_ptr<RectangleObject> asset_ptr) { m_seeker.visualAssetSet(asset_ptr); }

  std::shared_ptr<RectangleObject> trainObjectGet() { return m_train_object; }
  std::shared_ptr<RectangleObject> trainSeekerGet() { return m_seeker.objectGet(); }

  void SeekerStateMachine(float distance_travelled, bool train_at_station);

 private:
  RailWalker m_walker;
  StationSeeker m_seeker;
  //TrainNavigator* p_Route;
  //TrainPhysics* p_Physics;
  train_state m_State;
  clock_t m_duration_at_station = 0;
  int m_wait_time = 0;
  Vector2D current_waypoint;
  int m_train_id;
  std::shared_ptr<RectangleObject> m_visual_asset;
  Vector2D m_position;
  Vector2D m_vector;
  std::shared_ptr<RectangleObject> m_train_object;
};

#endif /* INCLUDE_GAME_TRAIN_HPP_ */
