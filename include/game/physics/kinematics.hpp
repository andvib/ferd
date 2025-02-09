#ifndef INCLUDE_GAME_PHYSICS_KINEMATICS_HPP_
#define INCLUDE_GAME_PHYSICS_KINEMATICS_HPP_

#include <Eigen/Dense>

struct position_t {
  float x;
  float y;
};

struct speed_t {
  float x;
  float y;
};

struct vector_t {
  float x;
  float y;
};

template <typename T>
concept HasXY = requires(T t) {
    { t.x } -> std::convertible_to<float>;
    { t.y } -> std::convertible_to<float>;
};

template <HasXY T>
inline bool operator==(const T& lhs, const T& rhs) {
    return (lhs.x == rhs.x && lhs.y == rhs.y);
}

using Vector2D = Eigen::Matrix<float, 2, 1>;

inline float absoluteSpeed(Vector2D speed_vec) {
  return sqrt((speed_vec(0) * speed_vec(0)) + (speed_vec(1) * speed_vec(1)));
}

inline float positionDistance(position_t pos1, position_t pos2) {
  return sqrt(pow((pos1.x - pos2.x), 2) + pow((pos1.y - pos2.y), 2));
}

#endif /* INCLUDE_GAME_PHYSICS_KINEMATICS_HPP_ */
