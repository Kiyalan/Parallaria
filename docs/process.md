### 2025.1.16 Kiyalan
Decided to employ C++20 standard and OpenGL 4.6 for developlemt.

OpenGL libraries include 4 parts: OpenGL, GLM, GLAD, GLFW. OpenGL are already supported by NVIDIA Geforce RTX 4060 and Intel Core Ultra 9185H, so it need only to be linked. Downloaded other 3 libraries.

GLFW is compiled into library using
```
cd code/opengl/glfw
cmake -S . -B build -G "MinGW Makefiles" -DBUILD_SHARED_LIBS=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_DOCS=OFF
cmake --build build
```
and linked in CMakeLists.txt in code/opengl.
Whether the compilation is necessary is unknown.
References: [glfw github](https://github.com/glfw/glfw), [glfw docs](https://www.glfw.org/docs/latest/index.html), [compile](https://www.glfw.org/docs/latest/compile.html) and [link](https://www.glfw.org/docs/latest/build_guide.html), [glfw cmake starter](https://github.com/enkisoftware/GLFW-CMake-starter), [cmake starter](https://github.com/stdrc/modern-cmake-by-example).

GLM is compiled in similar way.
References: [glm github](https://github.com/g-truc/glm)

GLAD is included manually.
References: [glad download](https://glad.dav1d.de/)

These four sublibraries are arranged into a larger library called opengl (code/opengl) for modular development.






