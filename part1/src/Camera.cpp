#include "Camera.hpp"

#include "glm/gtx/transform.hpp"

#include <iostream>

void Camera::MouseLook(int mouseX, int mouseY){
    
     if (firstMouse){
        lastX = mouseX;
        lastY = mouseY;
        firstMouse = false;
    }

    float xoffset = mouseX - lastX;
    float yoffset = lastY - mouseY;
    lastX = mouseX;
    lastY = mouseY;

    
    sensitivity = std::min(0.4f, tan(glm::radians(fov)/2)/tan(glm::radians(old_fov)/2));
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if(pitch > 89.0f){
        pitch = 89.0f;
    }
    if (pitch < -89.0f){
        pitch = -89.0f;
    }

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    m_viewDirection = glm::normalize(direction);
}

// OPTIONAL TODO: 
//               The camera could really be improved by
//               updating the eye position along the m_viewDirection.
//               Think about how you can do this for a better camera!

void Camera::MoveForward(float speed){
    glm::vec3 forwardVector = glm::normalize(m_viewDirection);

    m_eyePosition += forwardVector * speed;
}

void Camera::MoveBackward(float speed){
   glm::vec3 forwardVector = glm::normalize(m_viewDirection);

    m_eyePosition -= forwardVector * speed;
}

void Camera::MoveLeft(float speed){
    glm::vec3 leftVector = glm::normalize(glm::cross(m_viewDirection,m_upVector));

    m_eyePosition -= leftVector * speed;

}

void Camera::MoveRight(float speed){
     glm::vec3 leftVector = glm::normalize(glm::cross(m_viewDirection,m_upVector));

     m_eyePosition += leftVector * speed;
}

void Camera::MoveUp(float speed){
    m_eyePosition.y += speed;
}

void Camera::MoveDown(float speed){
    m_eyePosition.y -= speed;
}

void Camera::ProcessZoom(float yoffset){
    old_fov = fov;
    fov -= float(yoffset);
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 45.0f)
        fov = 45.0f;
    
    
}

// Set the position for the camera
void Camera::SetCameraEyePosition(float x, float y, float z){
    m_eyePosition.x = x;
    m_eyePosition.y = y;
    m_eyePosition.z = z;
}

float Camera::GetEyeXPosition(){
    return m_eyePosition.x;
}

float Camera::GetEyeYPosition(){
    return m_eyePosition.y;
}

float Camera::GetEyeZPosition(){
    return m_eyePosition.z;
}

float Camera::GetViewXDirection(){
    return m_viewDirection.x;
}

float Camera::GetViewYDirection(){
    return m_viewDirection.y;
}

float Camera::GetViewZDirection(){
    return m_viewDirection.z;
}
float Camera::getFOV(){
    return fov;
}


Camera::Camera(){
    std::cout << "(Constructor) Created a Camera!\n";
	// Position us at the origin.
    m_eyePosition = glm::vec3(0.0f,0.0f, 0.0f);
	// Looking down along the z-axis initially.
	// Remember, this is negative because we are looking 'into' the scene.
    m_viewDirection = glm::vec3(0.0f,0.0f, -1.0f);
	// For now--our upVector always points up along the y-axis
    m_upVector = glm::vec3(0.0f, 1.0f, 0.0f);

    lastX = 640;
    lastY = 360;
    pitch = 0.0f;
    yaw = -90.0f;
    fov = 45.0f;
    sensitivity = 0.3f;
}

glm::mat4 Camera::GetWorldToViewmatrix() const{
    // Think about the second argument and why that is
    // setup as it is.
    return glm::lookAt( m_eyePosition,
                        m_eyePosition + m_viewDirection,
                        m_upVector);
}