//
// Created by Ludw on 4/25/2024.
//

#include "../app.h"

void App::add_desc_set_layout(const uint32_t binding_count, const VkDescriptorSetLayoutBinding *p_bindings) {
    VkDescriptorSetLayoutCreateInfo desc_set_layout_info{};
    desc_set_layout_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    desc_set_layout_info.bindingCount = binding_count;
    desc_set_layout_info.pBindings = p_bindings;

    VkDescriptorSetLayout desc_set_layout;
    if (vkCreateDescriptorSetLayout(dev, &desc_set_layout_info, nullptr, &desc_set_layout) != VK_SUCCESS)
        throw std::runtime_error("failed to create descriptor set layout.");

    desc_set_layouts.push_back(desc_set_layout);
}

void App::add_pool_size(uint32_t desc_count, VkDescriptorType desc_type) {
    VkDescriptorPoolSize pool_size;
    pool_size.type = desc_type;
    pool_size.descriptorCount = desc_count;
    desc_pool_sizes.push_back(pool_size);
}

void App::create_desc_pool(uint32_t max_sets) {
    VkDescriptorPoolCreateInfo pool_info{};
    pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    pool_info.poolSizeCount = static_cast<uint32_t>(desc_pool_sizes.size());
    pool_info.pPoolSizes = desc_pool_sizes.data();
    pool_info.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
    pool_info.maxSets = max_sets;

    if (vkCreateDescriptorPool(dev, &pool_info, nullptr, &desc_pool) != VK_SUCCESS)
        throw std::runtime_error("failed to create descriptor pool.");

    VkDescriptorSetAllocateInfo alloc_info{};
    alloc_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    alloc_info.descriptorPool = desc_pool;
    alloc_info.descriptorSetCount = static_cast<uint32_t>(desc_set_layouts.size());
    alloc_info.pSetLayouts = desc_set_layouts.data();

    desc_sets.resize(desc_set_layouts.size());
    if (vkAllocateDescriptorSets(dev, &alloc_info, desc_sets.data()) != VK_SUCCESS)
        throw std::runtime_error("failed to allocate descriptor sets.");
}

void App::write_buf_desc_binding(const VCW_Buffer &buf, const uint32_t dst_set, const uint32_t dst_binding,
                                 const VkDescriptorType desc_type) const {
    VkDescriptorBufferInfo buf_info{};
    buf_info.buffer = buf.buf;
    buf_info.offset = 0;
    buf_info.range = buf.size;

    VkWriteDescriptorSet write{};
    write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    write.dstSet = desc_sets[dst_set];
    write.dstBinding = dst_binding;
    write.dstArrayElement = 0;
    write.descriptorType = desc_type;
    write.descriptorCount = 1;
    write.pBufferInfo = &buf_info;

    vkUpdateDescriptorSets(dev, 1, &write, 0, nullptr);
}

void App::write_sampler_desc_binding(VkSampler sampler, const uint32_t dst_set, const uint32_t dst_binding) const {
    VkDescriptorImageInfo img_info{};
    img_info.sampler = sampler;

    VkWriteDescriptorSet write{};
    write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    write.dstSet = desc_sets[dst_set];
    write.dstBinding = dst_binding;
    write.dstArrayElement = 0;
    write.descriptorType = VK_DESCRIPTOR_TYPE_SAMPLER;
    write.descriptorCount = 1;
    write.pImageInfo = &img_info;

    vkUpdateDescriptorSets(dev, 1, &write, 0, nullptr);
}

void App::write_img_desc_binding(const VCW_Image &img, const uint32_t dst_set, const uint32_t dst_binding,
                                 const VkDescriptorType desc_type) const {
    VkDescriptorImageInfo img_info{};
    img_info.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    img_info.imageView = img.view;
    if (img.combined_img_sampler)
        img_info.sampler = img.sampler;

    VkWriteDescriptorSet write{};
    write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    write.dstSet = desc_sets[dst_set];
    write.dstBinding = dst_binding;
    write.dstArrayElement = 0;
    write.descriptorType = desc_type;
    write.descriptorCount = 1;
    write.pImageInfo = &img_info;

    vkUpdateDescriptorSets(dev, 1, &write, 0, nullptr);
}

void App::write_img_desc_array(const std::vector<VCW_Image> &imgs, const uint32_t dst_set, const uint32_t dst_binding,
                               const VkDescriptorType desc_type) const {
    std::vector<VkDescriptorImageInfo> img_infos;
    for (auto &img: imgs) {
        VkDescriptorImageInfo img_info{};
        img_info.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        img_info.imageView = img.view;
        if (img.combined_img_sampler)
            img_info.sampler = img.sampler;
        img_infos.push_back(img_info);
    }

    VkWriteDescriptorSet write{};
    write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    write.dstSet = desc_sets[dst_set];
    write.dstBinding = dst_binding;
    write.dstArrayElement = 0;
    write.descriptorType = desc_type;
    write.descriptorCount = static_cast<uint32_t>(img_infos.size());
    write.pImageInfo = img_infos.data();

    vkUpdateDescriptorSets(dev, 1, &write, 0, nullptr);
}

void App::clean_up_desc() const {
    vkDestroyDescriptorPool(dev, desc_pool, nullptr);
    for (auto &desc_set_layout: desc_set_layouts) {
        vkDestroyDescriptorSetLayout(dev, desc_set_layout, nullptr);
    }
}
