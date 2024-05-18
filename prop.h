//
// Created by Ludw on 4/25/2024.
//

#ifndef VCW_PROP_H
#define VCW_PROP_H

#define WINDOW_TITLE "Vulkan App"

#define INITIAL_WIDTH 800
#define INITIAL_HEIGHT 600

#define MAX_FRAMES_IN_FLIGHT 2

#define APP_NAME "Vulkan App"
#define ENGINE_NAME "No Engine"

#define VERBOSE
#define VALIDATION

const std::vector<const char *> val_layers = {
        "VK_LAYER_KHRONOS_validation"
};

const std::vector<const char *> dev_exts = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
        // VK_EXT_PIPELINE_ROBUSTNESS_EXTENSION_NAME // not available
        // VK_EXT_HOST_QUERY_RESET_EXTENSION_NAME // not required anymore
};

//
// scaling resolution
//
#define FULLSCREEN_RES_DIV 1
// #define IMGUI_SCALE_OVERLAY

constexpr VkFormat PREFERRED_FORMAT = VK_FORMAT_B8G8R8A8_SRGB;
constexpr VkColorSpaceKHR PREFERRED_COLOR_SPACE = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
constexpr VkPresentModeKHR PREFERRED_PRES_MODE = VK_PRESENT_MODE_FIFO_KHR;
constexpr VkCompositeAlphaFlagBitsKHR PREFERRED_COMPOSITE_ALPHA = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;

constexpr VkImageUsageFlags SWAP_IMG_USAGE = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

constexpr VkComponentMapping DEFAULT_COMPONENT_MAPPING = {.r = VK_COMPONENT_SWIZZLE_IDENTITY, .g = VK_COMPONENT_SWIZZLE_IDENTITY, .b = VK_COMPONENT_SWIZZLE_IDENTITY, .a = VK_COMPONENT_SWIZZLE_IDENTITY};
constexpr VkImageSubresourceRange DEFAULT_SUBRESOURCE_RANGE = {.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT, .baseMipLevel = 0, .levelCount = 1, .baseArrayLayer = 0, .layerCount = 1};
constexpr VkImageSubresourceLayers DEFAULT_SUBRESOURCE_LAYERS = {VK_IMAGE_ASPECT_COLOR_BIT, 0, 0, 1};

constexpr VkBorderColor DEFAULT_SAMPLER_BORDER_COLOR = VK_BORDER_COLOR_INT_OPAQUE_BLACK;

#define MODEL_INDEX 2

#if MODEL_INDEX == 0
#define MODEL_PATH "models/armadillo/armadillo.obj"
#define TEXTURE_PATH "models/armadillo/"
#define CULL_MODE_FRONT
#endif

#if MODEL_INDEX == 1
#define MODEL_PATH "models/bunny/bunny.obj"
#define TEXTURE_PATH "models/bunny/"
#define CULL_MODE_FRONT
#endif

#if MODEL_INDEX == 2
#define MODEL_PATH "models/cornell-box/cornell-box.obj"
#define TEXTURE_PATH "models/cornell-box/"
#define CULL_MODE_BACK
#endif

#if MODEL_INDEX == 3
#define MODEL_PATH "models/cow/cow.obj"
#define TEXTURE_PATH "models/cow/"
#define CULL_MODE_FRONT
#endif

#if MODEL_INDEX == 4
#define MODEL_PATH "models/dragon/dragon.obj"
#define TEXTURE_PATH "models/dragon/"
#define CULL_MODE_FRONT
#endif

#if MODEL_INDEX == 5
#define MODEL_PATH "models/duck/duck.obj"
#define TEXTURE_PATH "models/duck/"
#define CULL_MODE_FRONT
#endif

#if MODEL_INDEX == 6
#define MODEL_PATH "models/lucy/lucy.obj"
#define TEXTURE_PATH "models/lucy/"
#define CULL_MODE_FRONT
#endif

#if MODEL_INDEX == 7
#define MODEL_PATH "models/sponza/sponza.obj"
#define TEXTURE_PATH "models/sponza/"
#define CULL_MODE_FRONT
#endif

#if MODEL_INDEX == 8
#define MODEL_PATH "models/suzanne/suzanne.obj"
#define TEXTURE_PATH "models/suzanne/"
#define CULL_MODE_FRONT
#endif

#if MODEL_INDEX == 9
#define MODEL_PATH "models/teapot/teapot.obj"
#define TEXTURE_PATH "models/teapot/"
#define CULL_MODE_FRONT
#endif

// Rasterization Stage
constexpr VkBool32 DEPTH_CLAMP_ENABLE = VK_FALSE;
constexpr VkBool32 RASTERIZER_DISCARD_ENABLE = VK_FALSE;
constexpr VkPolygonMode POLYGON_MODE = VK_POLYGON_MODE_FILL;
constexpr VkShaderStageFlags PUSH_CONSTANTS_STAGE = VK_SHADER_STAGE_ALL_GRAPHICS;
constexpr VkFrontFace FRONT_FACE = VK_FRONT_FACE_COUNTER_CLOCKWISE;
#ifdef CULL_MODE_NONE
constexpr VkCullModeFlags CULL_MODE = VK_CULL_MODE_NONE;
#endif
#ifdef CULL_MODE_FRONT
constexpr VkCullModeFlags CULL_MODE = VK_CULL_MODE_FRONT_BIT;
#endif
#ifdef CULL_MODE_BACK
constexpr VkCullModeFlags CULL_MODE = VK_CULL_MODE_BACK_BIT;
#endif

#define IMGUI_DESCRIPTOR_COUNT 1
#define DESCRIPTOR_TEXTURE_COUNT 32

//
// default values for camera
//
#define CAM_FOV 60.0f
#define CAM_SENSITIVITY 0.1f

#define CAM_NEAR 0.1f
#define CAM_FAR 4096.0f

#define CAM_MIN_PITCH (-89.0f)
#define CAM_MAX_PITCH 89.0f

#define CAM_YAW_SPACE 120.0f

#define CAM_SLOW 1.0f
#define CAM_FAST 10.0f

#endif //VCW_PROP_H