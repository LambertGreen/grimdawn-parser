cmake_minimum_required(VERSION 3.27)  # Minimum version of CMake required. Adjust as needed.
project(grimparse)  # Replace with your project name

# Set C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include FetchContent module to download dependencies
include(FetchContent)

# Download nlohmann/json
FetchContent_Declare(
  json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.10.5  # Specify the version you need
)

# Make nlohmann/json available to the project
FetchContent_MakeAvailable(json)

# Define your executable
add_executable(${PROJECT_NAME}
  common.cpp
  play_stats.cpp
  inventory_sack.cpp
  decrypt.cpp)

# Link nlohmann/json to your executable
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)

# Symlik compile_commands.json to project directory
if (CMAKE_EXPORT_COMPILE_COMMANDS)
  execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink
                  ${CMAKE_BINARY_DIR}/compile_commands.json
                  ${CMAKE_SOURCE_DIR}/compile_commands.json)
endif()
