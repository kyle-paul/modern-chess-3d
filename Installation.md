Build the GLFW 
```bash
cmake -S vendor/glfw \
      -B libs/glfw-build \
      -D GLFW_BUILD_TESTS=OFF \
      -D GLFW_BUILD_EXAMPLES=OFF \
      -D GLFW_BUILD_DOCS=OFF \
      -D GLFW_BUILD_WAYLAND=0

cmake --build libs/glfw-build --parallel <your-cpu-threads>
cmake --install libs/glfw-build --prefix libs/glfw-build/install
```

Build the GLM
```bash
cmake -S vendor/glm \
      -B libs/glm-build \
      -D GLM_BUILD_TESTS=OFF \
      -D BUILD_SHARED_LIBS=OFF

cmake --build libs/glm-build --parallel <your-cpu-threads> 
cmake --install libs/glm-build --prefix libs/glm-build/install
```

Build the ImGuiFileDialog
```bash
cmake -S vendor/ImGuiFileDialog \
      -B libs/ImGuiFileDialog-build

cmake --build libs/ImGuiFileDialog-build --parallel <your-cpu-threads> 
cmake --install libs/ImGuiFileDialog-build --prefix libs/ImGuiFileDialog-build/install
```