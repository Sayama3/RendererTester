cmake_minimum_required(VERSION 3.16)

set(CORE_SRC
        include/Core/Core.hpp
        include/Core/Logger.hpp
        src/Core/Logger.cpp
        include/Core/Profilier.hpp
        include/Math/Math.hpp
        src/Math/Math.cpp
)

add_library(Core STATIC ${CORE_SRC})

target_include_directories(Core PUBLIC include)
target_include_directories(Core PRIVATE src)

target_link_libraries(Core PUBLIC spdlog::spdlog_header_only tracy)
target_compile_features(Core PUBLIC cxx_std_20)