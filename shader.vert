#version 450

// #define USE_UNIFORM
#define USE_PUSH_CONSTANTS

#ifdef USE_PUSH_CONSTANTS
layout (push_constant) uniform PushConstants {
    mat4 view_proj;
    vec2 res;
    uint time;
} pc;
#endif

layout (location = 0) in vec3 in_pos;
layout (location = 1) in vec3 in_normal;
layout (location = 2) in vec3 in_color;
layout (location = 3) in vec2 in_uv;
layout (location = 4) in uint in_mat_id;

layout (location = 0) out vec3 normal;
layout (location = 1) out vec3 color;
layout (location = 2) out vec2 uv;
layout (location = 3) flat out uint mat_id;

mat4 x = mat4(
    vec4(1.0, 0.0, 0.0, 0.0),
    vec4(0.0, -1.0, 0.0, 0.0),
    vec4(0.0, 0.0, -1.0, 0.0),
    vec4(0.0, 0.0, 0.0, 1.0)
);

void main() {
    #ifdef USE_PUSH_CONSTANTS
    gl_Position = pc.view_proj * x * vec4(in_pos, 1.0);
    #else
    gl_Position = vec4(in_pos, 1.0);
    #endif

    normal = in_normal;
    color = in_color;
    uv = in_uv;
    mat_id = in_mat_id;
}
