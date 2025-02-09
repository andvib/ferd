#include "game/rail/straightRailPiece.hpp"

#include <spdlog/spdlog.h>

Vector2D StraightRailPiece::PositionOnRailGet(Vector2D current_position,
                                              float distance_travelled,
                                              RailDirection direction) {
    Vector2D norm_vector;

    if (direction == RailDirection::RAIL_DIRECTION_A_TO_B) {
        norm_vector = (m_wp_b->PositionVector() - m_wp_a->PositionVector()).normalized();
    } else {
        norm_vector = (m_wp_a->PositionVector() - m_wp_b->PositionVector()).normalized();
    }

    return current_position + (norm_vector * distance_travelled);
}

Vector2D StraightRailPiece::OrientationOnRailGet(Vector2D position_on_rail,
                                                 RailDirection direction) {
    if (direction == RailDirection::RAIL_DIRECTION_A_TO_B) {
        return (Vector2D(m_wp_b->PositionVector()) - m_wp_a->PositionVector()).normalized();
    } else {
        return (Vector2D(m_wp_a->PositionVector()) - m_wp_b->PositionVector()).normalized();
    }
}
