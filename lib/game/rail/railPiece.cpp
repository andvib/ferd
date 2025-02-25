#include "game/rail/railPiece.hpp"

#include <algorithm>

int RailPiece::waypointsSet(Waypoint *wp_a, Waypoint *wp_b) {
    if ((wp_a == nullptr) || (wp_b == nullptr)) {
        throw std::invalid_argument("Null pointer passed for one of the waypoints");
    }

    if (wp_a == wp_b) {
        throw std::invalid_argument("wp_a and wp_b are the same");
    }

    if (wp_a->PositionCoordinates() == wp_b->PositionCoordinates()) {
        throw std::invalid_argument("wp_a and wp_b are at the same location");
    }

    m_wp_a = wp_a;
    m_wp_b = wp_b;
    m_total_length = (wp_a->PositionVector() - wp_b->PositionVector()).norm();

    return 0;
}

bool RailPiece::IsPointOnPiece(Vector2D point) const {
    bool is_between_x = std::min((m_wp_a->PositionVector())(0),
                                 (m_wp_b->PositionVector())(0)) <= point(0) &&
                        point(0) <= std::max((m_wp_a->PositionVector())(0),
                                             (m_wp_b->PositionVector())(0));
    bool is_between_y = std::min((m_wp_a->PositionVector())(1),
                                 (m_wp_b->PositionVector())(1)) <= point(1) &&
                        point(1) <= std::max((m_wp_a->PositionVector())(1),
                                             (m_wp_b->PositionVector())(1));

    return is_between_x && is_between_y;
}
