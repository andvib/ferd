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

    private:
        position_t m_start_station;
        position_t m_end_station;
        position_t m_next_station;
};

#endif /* TRAIN_NAVIGATOR_HPP__ */
