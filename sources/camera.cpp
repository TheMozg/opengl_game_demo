#include "camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

const float DEFAULT_SPEED      = 4.5f;
const float DEFAULT_SENSITIVTY = 0.1f;

// Constructor with vectors
Camera::Camera(glm::vec3 position, float yaw, float pitch) {
    mPosition = position;
    mYaw = yaw;
    mPitch = pitch;
    mMovementSpeed = DEFAULT_SPEED;
    mMouseSensitivity = DEFAULT_SENSITIVTY;

    updateCameraVectors();
}

// Returns the view matrix calculated using Eular Angles and the LookAt Matrix
glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(mPosition, mPosition + mFront, mUp);
}

// Processes input received from a keyboard
void Camera::processKeyboard(CameraMovement direction, float deltaTime) {
    float velocity = mMovementSpeed * deltaTime;
    float oldUp = mPosition.y;
    switch (direction){
        case CameraMovement::FORWARD:
            mPosition += mFront * velocity;
            break;
        case CameraMovement::BACKWARD:
            mPosition -= mFront * velocity;
            break;
        case CameraMovement::LEFT:
            mPosition -= mRight * velocity;
            break;
        case CameraMovement::RIGHT:
            mPosition += mRight * velocity;
            break;
        default:
            break;
    }
    mPosition.y = oldUp;
}

// Processes input received from a mouse input system
void Camera::processMouse(float xoffset, float yoffset) {
    xoffset *= mMouseSensitivity;
    yoffset *= mMouseSensitivity;

    mYaw += xoffset;
    mPitch += yoffset;

    // Make sure that when pitch is out of bounds, screen doesn't get flipped
    if (mPitch > 89.0f)
        mPitch = 89.0f;
    if (mPitch < -89.0f)
        mPitch = -89.0f;

    // Update Front, Right and Up Vectors using the updated Eular angles
    updateCameraVectors();
}

glm::vec3 Camera::getPosition() {
    return mPosition;
}

void Camera::setPosition(glm::vec3 position) {
    mPosition = position;
}

// Calculates the front vector from the Camera's (updated) Eular Angles
void Camera::updateCameraVectors() {
    // Calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(mYaw)) * cos(glm::radians(mPitch));
    front.y = sin(glm::radians(mPitch));
    front.z = sin(glm::radians(mYaw)) * cos(glm::radians(mPitch));
    mFront = glm::normalize(front);
    // Also re-calculate the Right and Up vector
    // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    mRight = glm::normalize(glm::cross(mFront, worldUp));
    mUp = glm::normalize(glm::cross(mRight, mFront));
}
