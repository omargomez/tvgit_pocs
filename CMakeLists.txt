cmake_minimum_required(VERSION 4.0)

## Deps
# 1 libgit2

project(GitVison-POC LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)
find_package(libgit2 REQUIRED CONFIG)
add_subdirectory(tvision) ## Submodule
add_subdirectory(json) ## Submodule https://github.com/nlohmann/json.git

add_subdirectory(src/common)
add_subdirectory(src/model)
add_subdirectory(src/data)
add_subdirectory(src/app)

add_executable(hello src/main.cpp)
add_executable(repo_menu src/repo_menu.cpp ${MODEL_SOURCES} ${COMMON_SOURCES} ${DATA_SOURCES})
add_executable(branch_demo src/branch_app.cpp ${MODEL_SOURCES} ${COMMON_SOURCES} ${DATA_SOURCES})
target_include_directories(hello PRIVATE src src/common src/model src/data)
target_include_directories(repo_menu PRIVATE src src/common src/model src/data)
target_include_directories(branch_demo PRIVATE src src/common src/model src/data)
target_link_libraries(hello tvision libgit2::libgit2package)
target_link_libraries(repo_menu tvision libgit2::libgit2package nlohmann_json::nlohmann_json)
target_link_libraries(branch_demo tvision libgit2::libgit2package nlohmann_json::nlohmann_json)

## Main App
add_executable(simple ${MODEL_SOURCES} ${COMMON_SOURCES} ${DATA_SOURCES} ${APP_SOURCES})
target_include_directories(simple PRIVATE src src/common src/model src/data src/app)
target_link_libraries(simple tvision libgit2::libgit2package nlohmann_json::nlohmann_json)

add_custom_target(run
  COMMAND $<TARGET_FILE:branch_demo>
  DEPENDS branch_demo
  USES_TERMINAL
)
