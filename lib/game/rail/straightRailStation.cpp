#include "game/rail/straightRailStation.hpp"

void StraightRailStation::stopPointCalculate()
{
    m_stop_point = (m_wp_a->PositionVector() + m_wp_b->PositionVector()) / 2;
}
