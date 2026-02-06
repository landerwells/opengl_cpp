cmake_minimum_required(VERSION 3.25)
project(opengl_cpp)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set default build type to Debug if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# Debug flags
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -U_FORTIFY_SOURCE")

# Release flags  
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

# Export compile commands for LSP
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Enable testing
enable_testing()

## ~ FIND DEPENDENCIES (provided by Nix) ~
find_package(PkgConfig REQUIRED)

# Find GLFW
find_package(glfw3 3.4 REQUIRED)

# Find GLM
find_package(glm REQUIRED)

# Find OpenGL
find_package(OpenGL REQUIRED)

# GLAD - still need to fetch as it's generated code
include(FetchContent)

FetchContent_Declare(
    glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    GIT_TAG c
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_Populate(glad)
include_directories(${glad_SOURCE_DIR}/include)

# Fetch ImGui (not in nixpkgs in usable form)
FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG master
)
FetchContent_MakeAvailable(imgui)

# Fetch Google Test
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)

# STB is header-only, include from Nix
if(DEFINED ENV{STB_INCLUDE_PATH})
    include_directories($ENV{STB_INCLUDE_PATH})
else()
    # Fallback: fetch if not provided by Nix
    FetchContent_Declare(
        stb
        GIT_REPOSITORY https://github.com/nothings/stb.git
        GIT_TAG master
    )
    FetchContent_MakeAvailable(stb)
    include_directories(${stb_SOURCE_DIR})
endif()

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
    OpenGL::GL
)

## ~ COMPILER SETTINGS ~
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")
    if(NOT WIN32)
        set(GLAD_LIBRARIES dl)
    endif()
endif()

## ~ BUILD FILES ~
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
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS}
                               ${PROJECT_SHADERS} ${PROJECT_CONFIGS}
                               ${VENDORS_SOURCES})

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${imgui_SOURCE_DIR}
        ${imgui_SOURCE_DIR}/backends
)

# Link libraries
target_link_libraries(${PROJECT_NAME} 
    glfw 
    glm::glm
    imgui
    OpenGL::GL
    ${GLAD_LIBRARIES}
)

## ~ TESTS ~
add_subdirectory(tests)
