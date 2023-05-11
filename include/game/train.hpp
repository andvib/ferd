#ifndef TRAIN_HPP__
#define TRAIN_HPP__

#include "rectangleObject.hpp"

class Train : public RectangleObject
{
    public:
        Train();

        /**
         * @brief Construct a new Train object
         * 
         * @param x Start x-position
         * @param y Start y-position
         * @param color Color struct for color of the train
         */
        Train(float x, float y, const struct rectangle_color color);

        /**
         * @brief Construct a new Train object
         * 
         * @param x Start x-position
         * @param y Start y-position
         * @param speed Speed of the train
         * @param color Color struct for color of the train
         */
        Train(float x, float y, float speed, const struct rectangle_color color);

        /**
         * @brief Update the attributes of the train instance
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
        float m_speed = 0.002;
        float m_move_x = 0;
        float m_move_y = 0;
        int m_dir_x = 0;
        int m_dir_y = 0;

};

#endif /* TRAIN_HPP__ */
