#include "game/rail/stationSeeker.hpp"

#include <memory>

StationSeeker::StationSeeker(Vector2D start_position,
                             std::shared_ptr<RailPiece> piece,
                             std::shared_ptr<RailConnection> connection)
    : m_seeker_position(start_position) {
  set_current_rail(piece);
  set_next_connection(connection);

  m_seeker_object = std::make_shared<RectangleObject>(FERD_COLOR_3);
}

SeekerEvent StationSeeker::Update(float distance_travelled,
                                  bool train_at_station) {
  SeekerEvent event = SeekerEvent::NO_EVENT;

  switch (m_state) {
    using enum SeekerState;

    case MOVING:
      if (isStationPiece()) {
        m_seeker_position = stationPosition();
        m_state = AT_STATION;
        event = SeekerEvent::ARRIVED_AT_STATION;
      } else {
        m_seeker_position =
            nextPositionGet(m_seeker_position, distance_travelled * 1.2);
      }

      m_seeker_matrix = m_visual_asset->CalculateModelMatrix();
      m_seeker_object->objectLocationSet(m_seeker_position, Vector2D(1, 0));
      break;

    case AT_STATION:
      if (train_at_station) {
        m_state = MOVING;
        m_seeker_position = moveToNextRail();
      }
      break;
  }

  return event;
}
