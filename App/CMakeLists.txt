cmake_minimum_required(VERSION 3.16)

set(APP_SRC
        src/main.cpp
        include/App/Application.hpp
        src/App/Application.cpp
        src/App/Window.cpp
        include/App/Window.hpp
        src/App/Renderer.cpp
        include/App/Renderer.hpp
)

add_executable(App ${APP_SRC})

target_include_directories(App PUBLIC include)
target_include_directories(App PRIVATE src)

target_link_libraries(App PUBLIC Core imgui glad glfw)
target_compile_features(App PUBLIC cxx_std_20)