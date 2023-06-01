#ifndef TRAIN_PHYSICS_HPP__
#define TRAIN_PHYSICS_HPP__

#include "train_util.hpp"

#include <chrono>

class TrainPhysics
{
    public:
        TrainPhysics();

        /**
         * @brief Construct a new Train Physics object
         * 
         * @param start_pos Initial position of the train
         * @param acceleration Acceleration of the train
         */
        TrainPhysics(position_t start_pos, float acceleration);

        /**
         * @brief Update the physics attributes
         * 
         * @param delta_time_ms 
         */
        void Update(clock_t delta_time_ms);

        /**
         * @brief Get the Position object
         * 
         * @return position_t Current position of the train
         */
        position_t getPosition() {return m_pos;};

        /**
         * @brief Change the direction of the train
         */
        void changeDirection();

        /**
         * @brief Stop the train (sets speed to 0)
         */
        void stop();

    private:
        int m_direction;
        float m_speed;
        float m_acceleration;
        position_t m_pos;
};


#endif /* TRAIN_PHYSICS_HPP__ */
