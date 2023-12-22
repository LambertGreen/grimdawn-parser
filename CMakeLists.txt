cmake_minimum_required(VERSION 3.27)
project(grimparse)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include FetchContent module to download dependencies
include(FetchContent)

# Download jarro2783/cxxopts
FetchContent_Declare(
  cxxopts
  GIT_REPOSITORY https://github.com/jarro2783/cxxopts.git
  GIT_TAG origin/master  # Specify the version you need
)
FetchContent_MakeAvailable(cxxopts)

# Download nlohmann/json
FetchContent_Declare(
  json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.10.5  # Specify the version you need
)
FetchContent_MakeAvailable(json)


file(GLOB SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)
target_include_directories(${PROJECT_NAME} PRIVATE ${cxxopts_SOURCE_DIR}/include)

# Symlik compile_commands.json to project directory
if (CMAKE_EXPORT_COMPILE_COMMANDS)
  execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink
                  ${CMAKE_BINARY_DIR}/compile_commands.json
                  ${CMAKE_SOURCE_DIR}/compile_commands.json)
endif()
