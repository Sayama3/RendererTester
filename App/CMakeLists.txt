cmake_minimum_required(VERSION 3.16)

set(APP_SRC
        src/main.cpp
        include/App/Application.hpp
        src/App/Application.cpp
        src/App/Window.cpp
        include/App/Window.hpp
        src/Render/Renderer.cpp
        include/Render/Renderer.hpp
        src/Render/Buffer.cpp
        include/Render/Buffer.hpp
        src/Render/VertexArray.cpp
        include/Render/VertexArray.hpp
        src/Render/Mesh.cpp
        include/Render/Mesh.hpp
        src/Render/Shader.cpp
        include/Render/Shader.hpp
        src/App/Camera.cpp
        include/App/Camera.hpp
		src/App/ImGuiContext.cpp
		include/App/ImGuiContext.hpp
		src/Render/Texture.cpp
		include/Render/Texture.hpp
		include/vendor/stb_image.h
		src/App/ImGuiLib.cpp
		include/App/ImGuiLib.hpp
)

add_executable(App ${APP_SRC})

target_include_directories(App PUBLIC include)
target_include_directories(App PRIVATE src)

target_link_libraries(App PUBLIC Core)
target_link_libraries(App PRIVATE glad glfw)
target_compile_features(App PUBLIC cxx_std_20)