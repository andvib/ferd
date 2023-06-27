#ifndef TRAIN_HPP__
#define TRAIN_HPP__

#include "rectangleObject.hpp"
#include "trainNavigator.hpp"
#include "trainPhysics.hpp"

#include <chrono>

class Train : public RectangleObject
{
    public:
        Train();
        ~Train();

        /**
         * @brief Construct a new Train object
         * 
         * @param x Start position
         * @param y End position
         * @param color Color struct for color of the train
         */
        Train(position_t start, position_t end, const struct rectangle_color color);

        /**
         * @brief Construct a new Train object
         * 
         * @param x Start position
         * @param y End position
         * @param acceleration Acceleration of the train
         * @param color Color struct for color of the train
         */
        Train(position_t start, position_t end, float acceleration, const struct rectangle_color color);

        /**
         * @brief Update the physics model of the train, and navigate the route
         * 
         * @param delta_time_ms Time since previous update, in milliseconds
         */
        void Update(clock_t delta_time_ms) override;

        /**
         * @brief Calculate the model matrix for the train
         *
         * @return glm::mat4 Model matrix
         */
        glm::mat4 CalculateModelMatrix() override;

    private:
        TrainNavigator* p_Route;
        TrainPhysics* p_Physics;
};

#endif /* TRAIN_HPP__ */
