#ifndef CAMERA_HPP__
#define CAMERA_HPP__

#include <glm/gtc/matrix_transform.hpp>
#include "spdlog/spdlog.h"

struct cameraPos {
    double x, y;
};

struct cameraDimensions {
    float left, right, bottom, top;
};

class Camera {

    private:
        cameraPos Position;
        cameraDimensions Dimensions;
        float Speed;
    
    public:
        /**
         * @brief Construct a new Camera object
         *
         * @details Initializes the camera at the origin
         */
        Camera();

        /**
         * @brief Sets the position of the camera
         *
         * @details Positions the camera at the (x,y) coordinates, and points the camera to look
         *          at the same position from a higher z coordinate.
         *
         * @param x x-coordinate
         * @param y y-coordinate
         */
        void setPosition(double x, double y) {Position = {x, y};}

        /**
         * @brief Set the dimensions of the camera
         *
         * @details Sets the left, right, bottom and top boundaries of the camera projection.
         *
         * @param left Left boundary
         * @param right Right boundary
         * @param bottom Bootom boundary
         * @param top Top boundary
         */
        void setDimensions(float left, float right, float bottom, float top) {Dimensions = {left, right, bottom, top};};

        /**
         * @brief Set the Speed object
         * 
         * @param speed
         */
        void setSpeed(float speed) {Speed = speed;};

        /**
         * @brief Return the MVP matrix
         *
         * @details Calculates the MVP matrix associated with the camera. The model matrix must be
         *          given as output, and the MVP matrix can be fed directly to the shader uniform.
         *
         * @param model_matrix The current model matrix
         * @return glm::mat4 The MVP matrix
         */
        glm::mat4 transform(glm::mat4 model_matrix);

        /**
         * @brief Move the camera
         *
         * @details The move functions can be used to move the camera one unit. 
         */
        void moveUp() {Position.y += Speed;};
        void moveDown() {Position.y -= Speed;};
        void moveLeft() {Position.x -= Speed;};
        void moveRight() {Position.x += Speed;};
};

#endif /* CAMERA_HPP__ */
