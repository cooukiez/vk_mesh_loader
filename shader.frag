#version 450

layout(set = 0, binding = 0) uniform sampler samp;
layout(set = 0, binding = 1) uniform texture2D textures[8];

layout(location = 0) in vec3 normal;
layout(location = 1) in vec2 uv;
layout(location = 2) flat in uint mat_id;

layout(location = 0) out vec4 out_col;

void main() {
    out_col = texture(sampler2D(textures[mat_id], samp), uv);
}
