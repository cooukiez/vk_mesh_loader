//
// Created by Ludw on 4/26/2024.
//

#ifndef VCW_CAMERA_H
#define VCW_CAMERA_H

#include "../inc.h"
// ReSharper disable once CppUnusedIncludeDirective
#include "../prop.h"

class VCW_Camera {
public:
    glm::mat4 proj;
    glm::mat4 intermediate;

    // const
    glm::vec3 pos;
    glm::vec3 up;

    // depend on rotation
    glm::vec3 front;
    glm::vec3 right;

    float yaw;
    float body_yaw;
    float pitch;

    glm::vec3 mov_lin; // forward / backward
    glm::vec3 mov_lat; // sideways

    float speed;
    float sensitivity;
    float fov;

    float aspect_ratio; // height / width
    float near;
    float far;

    void create_default_cam(VkExtent2D res);

    void update_proj(VkExtent2D res);

    void update_cam_rotation(float dx, float dy);

    glm::mat4 get_view_proj() const;

    void move_cam(glm::vec3 movement);
};

#endif //VCW_CAMERA_H
