#ifndef TRAIN_NAVIGATOR_HPP__
#define TRAIN_NAVIGATOR_HPP__
#include "train_util.hpp"

#include <vector>

class TrainNavigator
{
    public:
        TrainNavigator();
    
        /**
         * @brief Construct a new Train Navigator object
         * 
         * @param start_station Position of start station
         * @param end_station Position of end station
         */
        TrainNavigator(position_t start_station, position_t end_station);

        /**
         * @brief Check if train is currently at a station
         * 
         * @param current_position Current position of the train
         * @return true Train is at station
         * @return false Train is not at station
         */
        bool atStation(position_t current_position);

        /**
         * @brief Get the vector to next station
         *
         * @details Calculates the unit vector from the previous to the next station
         *
         * @return vector_t Unit vector from the previous to the next station
         */
        vector_t vectorToNextStation();

        /**
         * @brief Get the distance to the next station based on the current position
         *
         * @param current_position Current position of the train
         * @return float Distance to station from the current position
         */
        float distanceToStation(position_t current_position);

    private:
        position_t m_start_station;
        position_t m_end_station;
        position_t m_next_station;
};

#endif /* TRAIN_NAVIGATOR_HPP__ */
