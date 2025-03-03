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

Train::Train() : RectangleObject(FERD_COLOR_1) {
  p_Route = new TrainNavigator();
  p_Physics = new TrainPhysics();

  m_train_id = get_next_train_id();
}

Train::Train(Line* line, Vector2D start_position, float acceleration,
             const struct ferd_color color)
    : RectangleObject(color) {
  p_Physics = new TrainPhysics((position_t){start_position(0), start_position(1)}, acceleration);
  p_Route = new TrainNavigator(line);

  p_Physics->rotateTrain(
      p_Route->vectorToNextWaypoint(p_Physics->getPosition()));
  m_State = STOPPED_AT_STATION;

  m_train_id = get_next_train_id();
}

Train::~Train() {
  delete p_Route;
  delete p_Physics;
}

void Train::Update(clock_t delta_time_ms) {
  switch (m_State) {
    case STOPPED_AT_STATION:
      if (m_duration_at_station == 0) {
        m_duration_at_station = clock();
        m_wait_time = rand() / (RAND_MAX / 3000);
        current_waypoint = p_Route->nextWaypointPos();
      }

      if (((clock() - m_duration_at_station) / CLOCKS_PER_MSEC) > m_wait_time) {
        m_State = ENROUTE;
        vector_t vector_next =
            p_Route->vectorToNextWaypoint(p_Physics->getPosition());
        p_Physics->rotateTrain({vector_next});
        p_Physics->accelerate();
        m_duration_at_station = 0;
      }
      break;

    case ENROUTE:
      p_Physics->Update(delta_time_ms);

      if (p_Route->atWaypoint(p_Physics->getPosition())) {
        spdlog::info("Train {} at waypoint", m_train_id);

        p_Physics->moveToStation(current_waypoint);
        vector_t vector_next =
            p_Route->vectorToNextWaypoint(p_Physics->getPosition());
        p_Physics->rotateTrain({vector_next});
        current_waypoint = p_Route->nextWaypointPos();
      }

      if (p_Route->distanceToStation(p_Physics->getPosition()) <
          p_Physics->getBreakingDistance()) {
        spdlog::info("Train {} is approaching station", m_train_id);
        p_Physics->decelerate();
        m_State = APPROACH;
      }
      break;

    case APPROACH:
      p_Physics->Update(delta_time_ms);

      if (p_Route->atStation(p_Physics->getPosition())) {
        p_Physics->stop();
        p_Physics->moveToStation(current_waypoint);
        m_State = STOPPED_AT_STATION;
      }
      break;
  }

  position_t current_position = p_Physics->getPosition();
  vector_t vector_next = p_Physics->getRotation();

  m_visual_asset->objectLocationSet(Vector2D(current_position.x, current_position.y),
                                    Vector2D(vector_next.x, vector_next.y));
}
