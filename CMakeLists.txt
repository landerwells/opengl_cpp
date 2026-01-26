cmake_minimum_required(VERSION 3.25)
project(opengl_cpp)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(GLFW_VERSION 3.4)
set(GLM_VERSION 1.0.1)

# Export compile commands for LSP
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Configure GLFW options
option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)

## ~ FETCH DEPENDENCIES ~
include(FetchContent)

# Fetch GLFW
FetchContent_Declare(
    glfw
    URL https://github.com/glfw/glfw/archive/refs/tags/${GLFW_VERSION}.tar.gz
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(glfw)

# Fetch ImGui
FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG master
)
FetchContent_MakeAvailable(imgui)

# Fetch GLM
FetchContent_Declare(
    glm
    URL https://github.com/g-truc/glm/archive/refs/tags/${GLM_VERSION}.tar.gz
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(glm)

# Fetch GLAD
FetchContent_Declare(
    glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    GIT_TAG c
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_Populate(glad)

# Fetch stb
FetchContent_Declare(
    stb
    GIT_REPOSITORY https://github.com/nothings/stb.git
    GIT_TAG master
)
FetchContent_MakeAvailable(stb)

# Include GLAD
include_directories(${glad_SOURCE_DIR}/include)

## ~ BUILD IMGUI AS A LIBRARY ~
add_library(imgui STATIC
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_demo.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui PUBLIC
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
)

target_link_libraries(imgui PUBLIC
    glfw
    ${OPENGL_LIBRARIES}
)

## ~ COMPILER SETTINGS ~
# Set compiler flags based on compiler
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU") # Check if using GCC
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")
    # -Wall -Wextra -Wpedantic
    if(NOT WIN32)
        set(GLAD_LIBRARIES dl)
    endif()
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang") # Check if using Clang
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
endif()

## ~ BUILD FILES ~
# Set which project you would like to build
set(B_TARGET "src")

# Set source files
file(GLOB VENDORS_SOURCES ${glad_SOURCE_DIR}/src/glad.c)
file(GLOB_RECURSE PROJECT_HEADERS ${B_TARGET}/*.h)
file(GLOB_RECURSE PROJECT_SOURCES ${B_TARGET}/*.cpp)
file(GLOB PROJECT_CONFIGS CMakeLists.txt
                          Readme.md
                         .gitattributes
                         .gitignore
                         .gitmodules)

# Add globs to sources
source_group("Headers" FILES ${PROJECT_HEADERS})
source_group("Sources" FILES ${PROJECT_SOURCES})
source_group("Vendors" FILES ${VENDORS_SOURCES})

# Important GLFW definitions
add_definitions(-DGLFW_INCLUDE_NONE
                -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")

## ~ BUILD PROJECTS ~
# Build your OpenGL/GLFW ray marcher with audio support
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS}
                               ${PROJECT_SHADERS} ${PROJECT_CONFIGS}
                               ${VENDORS_SOURCES})

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${stb_SOURCE_DIR}
        ${imgui_SOURCE_DIR}
        ${imgui_SOURCE_DIR}/backends
)

# Link libraries - order matters for some linkers
target_link_libraries(${PROJECT_NAME} 
    glfw 
    glm
    imgui
    ${GLAD_LIBRARIES}
)
