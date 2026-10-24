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

add_library(project_pch INTERFACE)
target_precompile_headers(project_pch INTERFACE
  <vector>    
  <string>
  <map>
  <set>
  <array>
  <algorithm>
  <memory>
  <utility>
  <iostream>
  <fstream>
  <sstream>
  <string_view>
  <thread>
  <mutex>
  "src/common/libgit_util.hpp"
)

add_executable(gitclient src/gitclient.cpp)
target_include_directories(gitclient PRIVATE include src/common)
target_link_libraries(gitclient libgit2::libgit2package project_pch)
## Main App
add_executable(tvgit src/tvgit_main.cpp ${MODEL_SOURCES} ${COMMON_SOURCES} ${DATA_SOURCES} ${APP_SOURCES})
target_include_directories(tvgit PRIVATE src src/common src/model src/data src/app)
target_link_libraries(tvgit tvision libgit2::libgit2package nlohmann_json::nlohmann_json project_pch)

### Repos test target
add_executable(repo_test src/repo_test.cpp ${MODEL_SOURCES} ${COMMON_SOURCES} ${DATA_SOURCES})
target_include_directories(repo_test PRIVATE src src/common src/model src/data)
target_link_libraries(repo_test tvision libgit2::libgit2package nlohmann_json::nlohmann_json)
