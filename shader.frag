#version 450
#extension GL_EXT_debug_printf: enable

layout (set = 0, binding = 0) uniform UBO {
    uint use_textures;
} ubo;
layout (set = 0, binding = 1) uniform sampler samp;
layout (set = 0, binding = 2) uniform texture2D textures[32];

layout (location = 0) in vec3 normal;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 uv;
layout (location = 3) flat in uint mat_id;

layout (location = 0) out vec4 out_col;

void main() {
    out_col = ubo.use_textures != 0 ? texture(sampler2D(textures[mat_id], samp), uv) : vec4(color, 1);
}