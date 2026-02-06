# Tests CMakeLists.txt

# Collect all test source files
file(GLOB_RECURSE TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

# Collect source files from main project that need to be tested
# Add your implementation files here (not main.cpp)
set(PROJECT_TEST_SOURCES
    ${CMAKE_SOURCE_DIR}/src/Transform.cpp
    # Add other .cpp files you want to test here
    # ${CMAKE_SOURCE_DIR}/src/OtherClass.cpp
)

# Only create test executable if there are test sources
if(TEST_SOURCES)
    # Create test executable with both test sources and project sources
    add_executable(run_tests ${TEST_SOURCES} ${PROJECT_TEST_SOURCES})

    # Include directories for tests
    target_include_directories(run_tests
        PRIVATE
            ${CMAKE_SOURCE_DIR}/src
            ${stb_SOURCE_DIR}
            ${imgui_SOURCE_DIR}
            ${imgui_SOURCE_DIR}/backends
    )

    # Link against Google Test, project dependencies, and any libraries your src needs
    target_link_libraries(run_tests
        PRIVATE
            gtest
            gtest_main
            gmock
            gmock_main
            glfw
            glm
            imgui
            ${GLAD_LIBRARIES}
    )

    # If you have source files from your main project that you want to test,
    # you can create a library from them and link it here
    # Example:
    # add_library(project_lib STATIC ${PROJECT_SOURCES})
    # target_link_libraries(run_tests PRIVATE project_lib)

    # Discover tests for CTest
    gtest_discover_tests(run_tests)

    # Add a custom target to run tests with verbose output
    add_custom_target(test_verbose
        COMMAND ${CMAKE_CTEST_COMMAND} --verbose
        DEPENDS run_tests
    )
else()
    message(WARNING "No test source files found in ${CMAKE_CURRENT_SOURCE_DIR}. Skipping test target creation.")
endif()
