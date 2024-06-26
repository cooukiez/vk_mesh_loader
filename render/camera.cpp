//
// Created by Ludw on 4/26/2024.
//

#include "camera.h"

void VCW_Camera::create_default_cam(VkExtent2D res) {
    pos = glm::vec3(0.0f, 0.0f, 0.0f);
    up = glm::vec3(0.0f, 1.0f, 0.0f);

    yaw = -90.0f;
    body_yaw = yaw;
    pitch = 0.0f;

    speed = CAM_SLOW;
    sensitivity = CAM_SENSITIVITY;
    fov = CAM_FOV;

    near = CAM_NEAR;
    far = CAM_FAR;

    speed_fast = CAM_FAST;
    speed_slow = CAM_SLOW;

    update_proj(res);
}

void VCW_Camera::update_proj(const VkExtent2D res) {
    aspect_ratio = static_cast<float>(res.width) / static_cast<float>(res.height);
    proj = glm::perspective(glm::radians(fov), aspect_ratio, near, far);
}

void VCW_Camera::update_cam_rotation(const float dx, const float dy) {
    yaw += dx * sensitivity;
    pitch += dy * sensitivity;

    yaw = glm::clamp(yaw, body_yaw - CAM_YAW_SPACE, body_yaw + CAM_YAW_SPACE);
    pitch = glm::clamp(pitch, CAM_MIN_PITCH, CAM_MAX_PITCH);

    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);

    right = glm::normalize(glm::cross(front, up));

    mov_lin = front * speed;
    mov_lat = right * speed;
}

glm::mat4 VCW_Camera::get_view_proj() const {
    const glm::mat4 view = glm::lookAt(pos, pos + front, up);

    return proj * view;
}

void VCW_Camera::move_cam(glm::vec3 movement) {
    body_yaw = yaw;
    pos += movement;
}

void VCW_Camera::set_speed(const bool fast) {
    speed = fast ? speed_fast : speed_slow;
}