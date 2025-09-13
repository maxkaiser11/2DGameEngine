cmake_minimum_required(VERSION 3.20)
project(2DGameEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(USE_VCPKG "Use vcpkg (CONFIG packages)" ON)

# ---- Sources ----
file(GLOB_RECURSE SRC_ALL CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
)
file(GLOB IMGUI_CORE
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui/imgui.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui/imgui_demo.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui/imgui_draw.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui/imgui_tables.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui/imgui_widgets.cpp
)
file(GLOB IMGUI_BACKENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui/imgui_impl_sdl2.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui/imgui_impl_sdlrenderer2.cpp
)

add_executable(${PROJECT_NAME} ${SRC_ALL} ${IMGUI_CORE} ${IMGUI_BACKENDS}
        src/Game/LevelLoader.cpp
        src/Game/LevelLoader.h)

target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/libs
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/glm
)

if (WIN32)
    target_compile_definitions(${PROJECT_NAME} PRIVATE WIN32_LEAN_AND_MEAN NOMINMAX)
endif()

# ---- SDL deps ----
if (USE_VCPKG)
    find_package(SDL2 CONFIG REQUIRED)
    find_package(SDL2_image CONFIG REQUIRED)
    find_package(SDL2_ttf   CONFIG REQUIRED)
    find_package(SDL2_mixer CONFIG REQUIRED)
    find_package(Lua REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE
            SDL2::SDL2
            SDL2::SDL2main
            SDL2_image::SDL2_image
            SDL2_ttf::SDL2_ttf
            SDL2_mixer::SDL2_mixer
            ${LUA_LIBRARIES}
    )

    target_link_libraries(${PROJECT_NAME} PRIVATE ${LUA_LIBRARIES})
    target_include_directories(${PROJECT_NAME} PRIVATE ${LUA_INCLUDE_DIR})
endif()

# ---- Put the exe in a predictable place ----
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
foreach(cfg IN ITEMS Debug Release RelWithDebInfo MinSizeRel)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${cfg} ${CMAKE_BINARY_DIR}/bin)
endforeach()

# ---- Copy runtime data (assets, config, fonts, maps, etc.) ----
# Adjust these dirs to match your repo. They will be copied next to the exe.
set(RUNTIME_DATA_DIRS
        assets
        Assets
        data
        config
        Config
        fonts
        maps
        textures
)
foreach(dir IN LISTS RUNTIME_DATA_DIRS)
    if (EXISTS ${CMAKE_SOURCE_DIR}/${dir})
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_SOURCE_DIR}/${dir}
                $<TARGET_FILE_DIR:${PROJECT_NAME}>/${dir})
    endif()
endforeach()

# For Visual Studio: run from the folder where the data was copied
set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY $<TARGET_FILE_DIR:${PROJECT_NAME}>)

# Also provide the absolute asset root to the code if you prefer using it there:
target_compile_definitions(${PROJECT_NAME} PRIVATE ASSET_ROOT_PATH="$<SHELL_PATH:${CMAKE_SOURCE_DIR}>")

# ---- Warnings ----
if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /permissive- /utf-8)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()
