# vk_wrapper_cpp
Simple mesh loader / viewer written with the Vulkan-API and tinyobjloader in C++, based of https://vulkan-tutorial.com/ with chapter 27 depth buffering and chapter 28 model loading. Contains a simple class system and supports a compact fly cam to explore the model. Model loading is only for `.obj` files and is done with https://github.com/tinyobjloader/tinyobjloader.

## Building
### Dependencies
- Vulkan SDK
- GLFW
- tinyobjloader
- GLM