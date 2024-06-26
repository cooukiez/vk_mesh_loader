//
// Created by Ludw on 4/25/2024.
//

#ifndef VCW_APP_H
#define VCW_APP_H

#include "inc.h"
// ReSharper disable once CppUnusedIncludeDirective
#include "prop.h"
#include "util.h"

#include "render/camera.h"

#include <tiny_obj_loader.h>

//
// vulkan debug
//
VkResult create_debug_callback(VkInstance inst, const VkDebugUtilsMessengerCreateInfoEXT *p_create_inf,
                               const VkAllocationCallbacks *p_alloc, VkDebugUtilsMessengerEXT *p_debug_msg);

void destroy_debug_callback(VkInstance inst, VkDebugUtilsMessengerEXT debug_msg, const VkAllocationCallbacks *p_alloc);

void get_debug_msg_info(VkDebugUtilsMessengerCreateInfoEXT &debug_info);

VKAPI_ATTR VkBool32 VKAPI_CALL
debug_callback(VkDebugUtilsMessageSeverityFlagBitsEXT severity, VkDebugUtilsMessageTypeFlagsEXT msg_type,
               const VkDebugUtilsMessengerCallbackDataEXT *p_callback_data, void *p_user_data);

bool check_validation_support();

struct VCW_QueueFamilyIndices {
    std::optional<uint32_t> qf_graph;
    std::optional<uint32_t> qf_pres;

    bool is_complete() const {
        return qf_graph.has_value() && qf_pres.has_value();
    }
};

struct VCW_SwapSupport {
    VkSurfaceCapabilitiesKHR caps;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> pres_modes;
};

struct Vertex {
    glm::vec3 pos;
    glm::vec3 normal;
    glm::vec3 color;
    glm::vec2 uv;
    uint32_t mat_id;

    static VkVertexInputBindingDescription get_binding_desc();

    static std::array<VkVertexInputAttributeDescription, 5> get_attrib_descs();

    bool operator==(const Vertex& other) const {
        return pos == other.pos && normal == other.normal && uv == other.uv;
    }
};

template<> struct std::hash<Vertex> {
    size_t operator()(Vertex const& vertex) const noexcept {
        return ((hash<glm::vec3>()(vertex.pos) ^ (hash<glm::vec3>()(vertex.normal) << 1)) >> 1) ^ (hash<glm::vec2>()(vertex.uv) << 1);
    }
};

struct VCW_PushConstants {
    alignas(16) glm::mat4 view_proj;
    alignas(8) glm::vec2 res;
    alignas(4) uint32_t time;
};

struct VCW_Uniform {
    uint32_t use_textures;
    float shadow_attenuation;
};

struct VCW_Buffer {
    VkDeviceSize size;
    VkBuffer buf;
    VkDeviceMemory mem;
    void *p_mapped_mem = nullptr;
};

struct VCW_Image {
    VkImage img;
    VkDeviceMemory mem;

    VkImageView view;

    VkSampler sampler;
    bool combined_img_sampler = false;

    VkExtent3D extent;
    VkFormat format;
    VkImageLayout cur_layout;
};

struct VCW_RenderStats {
    double frame_time;
    double gpu_frame_time;
    double blit_img_time;
    uint32_t frame_count;
};

class App {
public:
    void run() {
        init_window();
        init_app();
        render_loop();
        clean_up();
    }

    GLFWwindow *window;
    bool resized = false;
    glm::vec2 mouse_pos;
    bool cursor_enabled = false;
    glm::ivec2 window_dim;
    glm::ivec2 window_pos;

    VkInstance inst;
    VkDebugUtilsMessengerEXT debug_msg;

    VkSurfaceKHR surf;

    VkPhysicalDevice phy_dev = VK_NULL_HANDLE;
    VkPhysicalDeviceMemoryProperties phy_dev_mem_props;
    VkPhysicalDeviceProperties phy_dev_props;

    std::vector<VkQueueFamilyProperties> qf_props;
    VCW_QueueFamilyIndices qf_indices;
    VkDevice dev;
    VkQueue q_graph;
    VkQueue q_pres;

    VkSwapchainKHR swap;
    std::vector<VCW_Image> swap_imgs;
    VkFormat swap_img_format;
    VkExtent2D swap_extent;
    VkExtent2D render_extent;

    VkRenderPass rendp;
    VkPipelineLayout pipe_layout;
    VkPipeline pipe;
    std::vector<VkFramebuffer> frame_bufs;
    std::vector<VCW_Image> render_targets;

    std::vector<VkDescriptorSetLayout> desc_set_layouts;
    std::vector<VkDescriptorPoolSize> desc_pool_sizes;
    VkDescriptorPool desc_pool;
    std::vector<VkDescriptorSet> desc_sets;

    VkCommandPool cmd_pool;
    std::vector<VkCommandBuffer> cmd_bufs;

    VCW_Image depth_img;

    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    VkSampler sampler;
    std::vector<VCW_Image> textures;

    std::vector<Vertex> vertices;
    VCW_Buffer vert_buf;
    glm::vec3 min_vert_coord;
    glm::vec3 max_vert_coord;
    std::vector<uint32_t> indices;
    int indices_count;
    VCW_Buffer index_buf;

    VkQueryPool query_pool;
    uint32_t frame_query_count;

    VCW_PushConstants push_const;

    VCW_Uniform ubo;
    std::vector<VCW_Buffer> unif_bufs;

    std::vector<VkSemaphore> img_avl_semps;
    std::vector<VkSemaphore> rend_fin_semps;
    std::vector<VkFence> fens;

    uint32_t cur_frame = 0;
    VCW_RenderStats stats;
    VCW_RenderStats readable_stats;

    VCW_Camera cam;

    //
    //
    //
    // function definitions
    //
    //

    void init_app();

    void render_loop();

    void clean_up();

    //
    // window
    //
    static void frame_buf_resized(GLFWwindow *window, int width, int height);

    static void cursor_callback(GLFWwindow *window, double nx, double ny);

    void init_window();

    //
    // vulkan / imgui instance
    //
    static std::vector<const char *> get_required_exts();

    void create_inst();

    void setup_debug_msg();

    void init_imgui() const;

    //
    //
    // vulkan primitives
    //
    // surface
    //
    void create_surf();

    //
    // physical device
    //
    static std::vector<VkQueueFamilyProperties> get_qf_props(VkPhysicalDevice loc_phy_dev);

    VCW_QueueFamilyIndices find_qf(VkPhysicalDevice loc_phy_dev) const;

    static bool check_phy_dev_ext_support(VkPhysicalDevice loc_phy_dev);

    VCW_SwapSupport query_swap_support(VkPhysicalDevice loc_phy_dev) const;

    bool is_phy_dev_suitable(VkPhysicalDevice loc_phy_dev) const;

    void pick_phy_dev();

    //
    // logical device
    //
    void create_dev();

    //
    // swapchain
    //
    static VkSurfaceFormatKHR choose_surf_format(const std::vector<VkSurfaceFormatKHR> &available);

    static VkPresentModeKHR choose_pres_mode(const std::vector<VkPresentModeKHR> &available);

    VkExtent2D choose_extent(const VkSurfaceCapabilitiesKHR &caps) const;

    void create_swap();

    void recreate_swap();

    void clean_up_swap();

    //
    // buffers
    //
    uint32_t find_mem_type(uint32_t type_filter, VkMemoryPropertyFlags mem_flags) const;

    VCW_Buffer create_buf(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags mem_props) const;

    void map_buf(VCW_Buffer *p_buf) const;

    void unmap_buf(VCW_Buffer *p_buf) const;

    void cp_data_to_buf(VCW_Buffer *p_buf, const void *p_data) const;

    void cp_buf(const VCW_Buffer &src_buf, const VCW_Buffer &dst_buf);

    void clean_up_buf(const VCW_Buffer &buf) const;

    //
    // images
    //
    VkFormat find_supported_format(const std::vector<VkFormat> &possible_formats, VkImageTiling tiling,
                                   VkFormatFeatureFlags features) const;

    VkFormat find_depth_format() const;

    static bool has_stencil_component(VkFormat format);

    VCW_Image create_img(VkExtent2D extent, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage,
                         VkMemoryPropertyFlags mem_props) const;

    void create_img_view(VCW_Image *p_img, VkImageAspectFlags aspect_flags) const;

    VkSampler create_sampler(VkFilter filter, VkSamplerAddressMode address_mode) const;

    void create_sampler(VCW_Image *p_img, VkFilter filter, VkSamplerAddressMode address_mode) const;

    static VkAccessFlags get_access_mask(VkImageLayout layout);

    static void transition_img_layout(VkCommandBuffer cmd_buf, VCW_Image *p_img, VkImageLayout layout,
                                      VkPipelineStageFlags src_stage, VkPipelineStageFlags dst_stage);

    static void cp_buf_to_img(VkCommandBuffer cmd_buf, const VCW_Buffer &buf, const VCW_Image &img, VkExtent2D extent);

    static void
    blit_img(VkCommandBuffer cmd_buf, const VCW_Image &src, VkExtent3D src_extent, const VCW_Image &dst, VkExtent3D dst_extent,
             VkFilter filter);

    static void blit_img(VkCommandBuffer cmd_buf, const VCW_Image &src, const VCW_Image &dst, VkFilter filter);

    static void copy_img(VkCommandBuffer cmd_buf, const VCW_Image &src, const VCW_Image &dst);

    void clean_up_img(const VCW_Image &img) const;

    //
    // descriptor pool
    //
    void add_desc_set_layout(uint32_t binding_count, const VkDescriptorSetLayoutBinding *p_bindings);

    void add_pool_size(uint32_t desc_count, VkDescriptorType desc_type);

    void create_desc_pool(uint32_t max_sets);

    void write_buf_desc_binding(const VCW_Buffer &buf, uint32_t dst_set, uint32_t dst_binding, VkDescriptorType desc_type) const;

    void write_img_desc_binding(const VCW_Image &img, uint32_t dst_set, uint32_t dst_binding, VkDescriptorType desc_type) const;

    void write_sampler_desc_binding(VkSampler sampler, uint32_t dst_set, uint32_t dst_binding) const;

    void write_img_desc_array(const std::vector<VCW_Image> &imgs, uint32_t dst_set, uint32_t dst_binding, VkDescriptorType desc_type) const;

    void clean_up_desc() const;

    //
    // pipeline prerequisites
    //
    void create_rendp();

    VkShaderModule create_shader_mod(const std::vector<char> &code) const;

    void create_render_targets();

    void create_frame_bufs(const std::vector<VCW_Image> &img_targets);

    void clean_up_pipe() const;

    //
    // render prerequisites
    //
    void create_cmd_pool();

    VkCommandBuffer begin_cmd() const;

    VkCommandBuffer begin_single_time_cmd() const;

    void end_single_time_cmd(VkCommandBuffer cmd_buf) const;

    void create_cmd_bufs();

    void create_sync();

    void create_query_pool(uint32_t loc_frame_query_count);

    void render();

    void clean_up_sync() const;

    //
    //
    // personalized vulkan initialization
    //
    void load_model();

    void create_vert_buf();

    void create_index_buf();

    void create_unif_bufs();

    void create_textures_sampler();

    void create_textures();

    void create_depth_resources();

    void create_desc_pool_layout();

    void create_pipe();

    void write_desc_pool() const;

    void update_bufs(uint32_t index_inflight_frame);

    void record_cmd_buf(VkCommandBuffer cmd_buf, uint32_t img_index) const;

    void fetch_queries(uint32_t img_index);
};

#endif //VCW_APP_H
