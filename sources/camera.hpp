#pragma once

#include <glm/glm.hpp>

enum class CameraMovement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP
};

class Camera {
public:
    // Constructor with vectors
    Camera(glm::vec3 position, float yaw, float pitch);

    // Returns the view matrix calculated using Eular Angles and the LookAt Matrix
    glm::mat4 getViewMatrix();

    // Processes input received from a keyboard
    void processKeyboard(CameraMovement direction, float deltaTime);

    // Processes input received from a mouse input system
    void processMouse(float xoffset, float yoffset);

    glm::vec3 getPosition();
    void setPosition(glm::vec3 position);

private:
    // Camera Attributes
    glm::vec3 mPosition;
    glm::vec3 mFront;
    glm::vec3 mUp;
    glm::vec3 mRight;
    // Eular Angles
    float mYaw;
    float mPitch;
    // Camera options
    float mMovementSpeed;
    float mMouseSensitivity;

    // Calculates the front vector from the Camera's (updated) Eular Angles
    void updateCameraVectors();
};
