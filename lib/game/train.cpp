#include "game/train.hpp"

#include <spdlog/spdlog.h>

#include <chrono>
#include <cstdlib>
#include <ctime>

#include "game/trainPhysics.hpp"

#define CLOCKS_PER_MSEC (CLOCKS_PER_SEC / 1000)

static get_next_train_id() {
  static int next_train_id = 1;
  return next_train_id++;
}

Train::Train(Vector2D start_position, const struct ferd_color color,
             std::shared_ptr<RailPiece> piece,
             std::shared_ptr<RailConnection> connection)
    : m_walker(), m_seeker(start_position, piece, connection) {
  m_State = STOPPED_AT_STATION;

  m_train_id = get_next_train_id();

  m_walker.set_current_rail(piece);
  m_walker.set_next_connection(connection);

  m_position = start_position;

  m_train_object = std::make_shared<RectangleObject>(color);
}

Train::~Train() {}

void Train::Update(clock_t delta_time_ms) {
  float distance_travelled = 0.01 * delta_time_ms;

  m_position = m_walker.nextPositionGet(m_position, distance_travelled);
  m_vector = m_walker.rotationGet(m_position);

  m_visual_asset->objectLocationSet(m_position, m_vector);
  SeekerEvent seeker_evt =
      m_seeker.Update(distance_travelled, m_walker.isStationPiece());

  if (seeker_evt == SeekerEvent::ARRIVED_AT_STATION) {
    spdlog::info("seeker found a station");
    /* Calculate distance to station */
    /* Prepare arrival at station */
    /* Can it go to APPROACH already? */
  }
}
