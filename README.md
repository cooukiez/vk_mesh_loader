# vk_mesh_loader
Simple mesh loader / viewer written with the Vulkan-API and tinyobjloader in C++,
based of the [Vulkan Tutorial from Alexander Overvoorde](https://vulkan-tutorial.com/) with chapter 27 depth buffering and chapter 28 model loading.
Contains a simple class system and supports a compact fly cam to explore the model. Model loading is
only for `.obj` files and is done with [tinyobjloader](https://github.com/tinyobjloader/tinyobjloader).

Model selection available via precompiler in `prop.h`, just change the `MODEL_INDEX`.

## Building
use vcpkg for Windows
### Dependencies
- Vulkan SDK
- GLFW
- tinyobjloader
- GLM

## ToDo
- [ ] Add more models
- [ ] Add more lighting models
- [ ] fix cornell box model ***again***